/*
 * Copyright (C) 2014 Microchip Technology Inc. and its subsidiaries.  You may use this software and any derivatives
 * exclusively with Microchip products.
 *
 * MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any derivatives created by any person or
 * entity by or on your behalf, exclusively with Microchip?s products.  Microchip and its licensors retain all ownership
 * and intellectual property rights in the accompanying software and in all derivatives hereto.
 *
 * This software and any accompanying information is for suggestion only.  It does not modify Microchip?s standard
 * warranty for its products.  You agree that you are solely responsible for testing the software and determining its
 * suitability.  Microchip has no obligation to modify, test, certify, or support the software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING,
 * BUT NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE
 * APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN
 * ANY APPLICATION.
 *
 * IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF
 * STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
 * TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
 * SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.
 *
 *
 * File:        bluetooth.c
 * Date:        January 20, 2015
 * Compiler:    XC16 v1.23
 *
 * Functions to communicate with a RN4020 Bluetooth LE module over a UART
 * 
 */

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "bluetooth.h"
#include "config.h"
#include "app.h"
#include "uart.h"
#include "timers.h"
#include <stdlib.h>
#include <string.h>

extern APP_DATA appData;

uint16_t BT_CheckFwVer(void);

struct gatts_service_inst gatts_service[] = {
	{
		.gatts_if = 0, /* gatts_if not known yet, so initial is ESP_GATT_IF_NONE */
	},
	{
		.gatts_if = 0, /* gatts_if not known yet, so initial is ESP_GATT_IF_NONE */
	}
};

struct gatts_char_inst gatts_char[] = {
	{
		/* Battery Service -> Battery Level */
		.service_pos = 0, // Battery service
		.char_perm = ESP_GATT_PERM_READ,
		.char_property = "",
		.char_val = NULL,
		.char_handle = "0032",
		.char_nvs = "2A19"
	},
	{
		.service_pos = 1, // heart rate service
		.char_perm = ESP_GATT_PERM_READ,
		.char_property = "22,02",
		.char_val = NULL,
		.char_handle = "001B",
		.char_nvs = "2A37"
	}
};

uint16_t get_char_handle(struct gatts_char_inst *bt, char *rxbuf)
{
	char* pch;
	uint8_t state = 0;

	char* tempBuf = (char*) malloc(strlen(rxbuf) + 1);
	if (!tempBuf) {
		return false;
	}
	strcpy(tempBuf, rxbuf);
	//Parse response line by line
	pch = strtok(tempBuf, "\r\n");
	do {
		switch (state) {
		case 0:
			//Check if the line contains a service
			if (strstr(pch, bt->char_nvs)) {
				//Service found, now looking for line with characteristic
				state = 1;
				break;
			}
			break;
		case 1:
			if (strncmp(pch, "  ", 2)) {
				//String doesn't start with two spaces, so this is not a characteristic.  This is an error.
				free(tempBuf);
				return 0;
			}
			if (strstr(pch, bt->char_nvs)) {
				//Characteristic found, now looking for handle
				char* pch2 = strchr(pch, ',') + 1;
				uint16_t handle;
				if (sscanf(pch2, "%x,", &handle) == 1) {
					//#if DEBUG_LEVEL >= DEBUG_ALL
					//                    sPortDebug->println("Setting handle");
					//                    sPortDebug->println(handle, HEX);
					//#endif
					free(tempBuf);
					return handle;

				}
				state = 0;
				break;
			}
		}
		pch = strtok(NULL, "\r\n");
	} while (pch != NULL);
	free(tempBuf);
	return 0;
}

void clear_bt_port(void)
{
	while (UART_IsNewRxData()) { //While buffer contains old data
		UART_ReadRxBuffer(); //Keep reading until empty
		if (!UART_IsNewRxData()) {
			WaitMs(100);
		}
	}
	//Clear any UART error bits
	U1STAbits.FERR = 0;
	U1STAbits.PERR = 0;
}


//**********************************************************************************************************************
// Receive a message over the Bluetooth link

bool BT_ReceivePacket(char * Message)
{
	static enum BluetoothDecodeState btDecodeState = WaitForCR; //Static so maintains state on reentry   //Byte read from the UART buffer
	static uint16_t i = 0;

	if (UART_IsNewRxData()) //Check if new data byte from BT module and return if nothing new
	{
		Message[i++] = UART_ReadRxBuffer();
		if (i == BT_RX_PKT_SZ) {
			i = 0;
		}

		if (!appData.rn_4871_packets) {
			switch (btDecodeState) {
			case WaitForCR:
				if (Message[i - 1] == '\r') { //See if this is the CR
					btDecodeState = WaitForLF; //Is CR so wait for LF
				}
				break;

			case WaitForLF:
				btDecodeState = WaitForCR; //Will be looking for a new packet next
				if (Message[i - 1] == '\n') //See if this is the LF
				{
					Message[i] = NULL; //Got a complete message!
					i = 0;
					return true;
				}
				break;

			default: //Invalid state so start looking for a new start of frame
				btDecodeState = WaitForCR;
			}

		} else {
			appData.rn_4871_packets = false;
			if (Message[i - 1] == '#') //See if this is the end
			{
				btDecodeState = WaitForCR; //Will be looking for a new packet next
				Message[i] = NULL; //Got a complete message!
				i = 0;
				return true;
			}
		}
	}
	return false;
}

//**********************************************************************************************************************
// Send a command to the RN4020 module
//Return true for success, false for busy

bool BT_SendCommand(const char *data, bool wait)
{
	uint16_t i;
	//Only transmit a message if TX timer expired, or wait flag is set to false
	//We limit transmission frequency to avoid overwhelming the BTLE link
	if (TimerDone(TMR_BT_TX) || wait == false) {
		for (i = 0; i < SIZE_TxBuffer; i++) {
			if (*data != '\0') //Keep loading bytes until end of string
				UART_WriteTxBuffer(*data++); //Load byte into the transmit buffer
			else
				break;
		}
		UART_TxStart(); //Start transmitting the bytes
		StartTimer(TMR_BT_TX, BT_TX_MS); //Restart transmit timer
		return true;
	}
	return false;
}

//**********************************************************************************************************************
// Send a byte to the RN4020 module

void BT_SendByte(char data)
{
	UART_WriteTxBuffer(data); //Load byte into the transmit buffer
	UART_TxStart(); //Start transmitting the byte
}

//**********************************************************************************************************************
// Get a response from the RN4020 module

bool BT_GetResponse(char *data)
{
	uint16_t byteCount = 0;
	char newByte;

	StartTimer(TMR_RN_COMMS, 600); //Start 600ms timeout for routine

	while (byteCount < BT_RX_PKT_SZ) //Don't accept more than the buffer size
	{
		if (UART_IsNewRxData()) //Check if new data byte from BT module and return if nothing new
		{
			newByte = UART_ReadRxBuffer(); //Read the data byte for processing
			*data++ = newByte; //Add it to the buffer
			byteCount++; //Keep track of the number of bytes received
			if (newByte == '\n') //Check if got linefeed
				return true; //If linefeed then return success
		}
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			return false; //If timed out then return failure
	}
	return false;
}

//**********************************************************************************************************************
// Compare the buffer with the response with one of the expected responses

bool BT_CompareResponse(const char *data1, const char *data2)
{
	uint16_t i;

	for (i = 0; i < 50; i++) //Compare up to 50 bytes
	{
		if (*data1 == '\0') //See if reached end of string with no bytes different
			return true; //No bytes were different so return success
		else if (*data1++ != *data2++) //else see if the bytes are different
			return false; //Bytes differ so return failure
	}
	return false; //Did not reach end of string so return failure
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response

bool BT_CheckResponse(const char *data)
{
	uint16_t i, ByteCount = 0;
	char NewByte, Buffer[50], *BufPtr;

	StartTimer(TMR_RN_COMMS, 600); //Start 600ms timeout for routine

	BufPtr = Buffer;
	while (ByteCount < 50) //Don't accept more than the buffer size
	{
		if (UART_IsNewRxData()) //Check if new data byte from BT module and return if nothing new
		{
			NewByte = (char) UART_ReadRxBuffer(); //Read the data byte for processing
			*BufPtr++ = NewByte; //Add it to the buffer
			ByteCount++;
			if (NewByte == '\n') //Check if got linefeed
				break; //If linefeed then we have what we want
		}
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			return false; //If timed out then return failure
	}

	BufPtr = Buffer;
	for (i = 0; i < ByteCount; i++) //Compare all bytes received
	{
		if (*data == '\0') //See if reached end of string with no bytes different
			return true; //No bytes were different so return success
		else if (*data++ != *BufPtr++) //else see if the bytes are different
			return false; //Bytes differ so return failure
	}
	return true; //All bytes matched so return success
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response
//   All incoming bytes in the position of the wildcard character are ignored
//   Use this to ignore text that changes, like MAC addresses.

bool BT_CheckResponseWithWildcard(const char *data, char Wildcard)
{
	uint16_t i, ByteCount = 0;
	char NewByte, Buffer[50], *BufPtr;

	StartTimer(TMR_RN_COMMS, 600); //Start 600ms timeout for routine

	BufPtr = Buffer;
	while (ByteCount < 50) //Don't accept more than the buffer size
	{
		if (UART_IsNewRxData()) //Check if new data byte from BT module and return if nothing new
		{
			NewByte = UART_ReadRxBuffer(); //Read the data byte for processing
			*BufPtr++ = NewByte; //Add it to the buffer
			ByteCount++;
			if (NewByte == '\n') //Check if got linefeed
				break; //If linefeed then we have what we want
		}
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			return false; //If timed out then return failure
	}

	BufPtr = Buffer;
	for (i = 0; i < ByteCount; i++) //Compare all bytes received
	{
		if (*data == '\0') //See if reached end of string with no bytes different
			return true; //No bytes were different so return success
		else if (*data == Wildcard) //else see if expected response byte is a wildcard
		{
			data++; //Increment past wildcard byte
			BufPtr++; //Increment to ignore byte corresponding to wildcard
		} else if (*data++ != *BufPtr++) //else see if the bytes are different
			return false; //Bytes differ so return failure
	}
	return true; //All bytes matched or were ignored so return success
}

/* update firmware via wireless app */
bool BT_check_upd(void)
{
	/* Jumper on DFU OTA UPDATE */
	BT_OTA_UPD_TRIS = 1; // set for jumper input
	CNPU1bits.CN7PUE = 1; // pullup for RB3
	WaitMs(2); // jumper pullup read delay, rise time is slow
	if (BT_OTA_UPD == 0) {
		BT_OTA_UPD_TRIS = 0; // set back to output
		BT_WAKE_SW = 1;
		BT_WAKE_HW = 1;
		BT_CMD = 0;

		WaitMs(100);
		BT_SendCommand("SF,2\r", false); // perform complete factory reset
		WaitMs(100);
		BT_CheckResponse(AOK);

		BT_SendCommand("SF,2\r", false); // perform complete factory reset again
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		BT_SendCommand("SDH,4.1\r", false); // defaults
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
		BT_SendCommand("SDM,RN4020\r", false); // defaults
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		BT_SendCommand("SDN,Microchip\r", false); // defaults
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		BT_SendCommand("SP,7\r", false); // defaults
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		BT_SendCommand("SS,C0000000\r", false); // add service
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		BT_SendCommand("SR,32008000\r", false); // support MLDP, enable OTA (peripheral mode is enabled by default)
		WaitMs(100);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
		BT_SendCommand("R,1\r", false); //Force reboot

		//Wait for WS status high
		StartTimer(TMR_RN_COMMS, 4000); //Start 4s timeout
		while (BT_WS == 0) {
			if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			{
				return false;
			}
		}

		//Wait for end of "CMD\r\n" - we don't check for full "CMD\r\n" string because we may 
		//miss some bits or bytes at the beginning while the UART starts up
		StartTimer(TMR_RN_COMMS, 4000); //Start 4s timeout
		while (UART_ReadRxBuffer() != '\n') {
			if (TimerDone(TMR_RN_COMMS)) //Check if timed out
			{
				return false;
			}
		}

		BT_SendCommand("I\r", false); // MLDP mode
		BT_SendCommand("A\r", false); // start advertising

		/* wait loop controller for power cycle/reset after firmware update */
		while (true) {
			while (true) { // fast flash waiting for OTA
				ClrWdt();
				while (UART_IsNewRxData()) { //While buffer contains old data
					UART_ReadRxBuffer(); //Keep reading until empty
					if (!UART_IsNewRxData()) {
						WaitMs(200);
					}
				}
				WaitMs(110);
				SLED = !SLED;
			}

		}

	}
	BT_OTA_UPD_TRIS = 0;
	return true;
}

//**********************************************************************************************************************
// Set up the RN4020 module

bool BT_SetupModule_4020(void)
{
	uint16_t version_code;

	/* check for over the air firmware updates */
	BT_check_upd();

	//Check RN4020 module's firmware version for version specific setups
	version_code = BT_CheckFwVer();

	BT_SendCommand("sf,2\r", false); // Factory reset
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//Send "GR" to get feature settings
	BT_SendCommand("gr\r", false); //Get RN4020 module feature settings
	if (!BT_CheckResponse("26060000\r\n")) //Check if features are set for auto advertise and flow control, No Input, no output, no direct advertisement
	{ //auto enable MLDP, suppress messages during MLDP
		BT_SendCommand("sr,26060000\r", false); //Features not correct so set features
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
	}

	char macAddr[16];
	BT_SendCommand("gds\r", false); // Get mac address
	while (!BT_ReceivePacket(macAddr));

	char message[12];
	macAddr[12] = '\0';
	sprintf(message, "sn,%s_BT\r", &macAddr[8]);

	BT_SendCommand(message, false); //Set advertise name
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	BT_SendCommand("gs\r", false);
	if (!BT_CheckResponse("F0000001\r\n")) {
		//Send "SS" to set user defined private profiles and ID/Battery in 1.33 firmware
		BT_SendCommand("ss,F0000001\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
	}

	BT_SendCommand("s-,FRC-\r", false); // set serialized name  Bluetooth-friendly name
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//  initial connection parameters 
	BT_SendCommand("st,003c,0000,0064\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Clear all settings of defined services and characteristics
	BT_SendCommand("pz\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	if (version_code >= 33) { // V1.33.4 public services
		// Public BTLE services and characteristics

		// heart rate service with standard 16-bit UUID
		BT_SendCommand("ps,"PUBLIC_HR_UUID"\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart rate measurement characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_HRM",12,04\r", false); //Notify, Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart body sensor location characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_BSL",06,01\r", false); //Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart rate control point characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_RCP",06,01\r", false); //Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		//  Automation IO service with standard 16-bit UUID
		BT_SendCommand("ps,"PUBLIC_AIO_UUID"\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO digital characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_DIG",16,08,33\r", false); //Notify, Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO analog characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_ANA",16,02,33\r", false); //Notify, Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO agg characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_AGG",12,0F,33\r", false); //Notify, Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
	}

	// set power to max
	BT_SendCommand("sp,7\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// set software version
	BT_SendCommand("sdr,"APP_VERSION_STR"\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Private BTLE services and characteristics

	//Send "ps" to set user defined service UUID
	BT_SendCommand("ps,"PRIVATE_SERVICE",\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom button characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_SWITCHES",22,02\r", false); //Notify, Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom potentiometer characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_POTENTIOMETER",22,02\r", false); //Notify, Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom LED characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_LEDS",0A,04\r", false); //Write , Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom RELAY characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_RELAYS",0A,04\r", false); //Write , Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom analog input characteristic with generated UUID //Write , Read
	BT_SendCommand("pc,"PRIVATE_CHAR_ADC_CHAN",0A,04\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom digital device characteristic with generated UUID //Write , Read
	BT_SendCommand("pc,"PRIVATE_CHAR_PIC_SLAVE",0A,0F\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	BT_SendCommand("wc\r", false); //Command to clear script, just in case there is a script
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//Send "R,1" to save changes and reboot
	return BT_RebootEnFlow(true);
}

//**********************************************************************************************************************
// Set up the RN4871 module

bool BT_SetupModule_4871(void)
{
	uint16_t version_code;

	/* check for over the air firmware updates */
	//	BT_check_upd();

	//Check RN4871 module's firmware version for version specific setups
	//	version_code = BT_CheckFwVer();
	version_code = 118; // hardcode for now

	//Send "GR" to get feature settings
	//	BT_SendCommand("GN\r", false);
	//	BT_SendCommand("GR\r", false); //Get module feature settings
	//	BT_SendCommand("gs\r", false);
	// Clear all settings of defined services and characteristics
	BT_SendCommand("pz\r", false); // must reboot next to clear handles
	BT_SendCommand("SF,1\r", false); // Factory reset
	WaitMs(500);

	//Clear any UART error bits
	U1STAbits.FERR = 0;
	U1STAbits.PERR = 0;

	// BTCMD("$");
	BT_SendCommand("$", false);
	WaitMs(100);
	// BTCMD("$$$");
	BT_SendCommand("$$$", false);
	WaitMs(500);

	// assign delimiters
	BT_SendCommand("S%,%,#\r", false);
	WaitMs(100);

	U1RTS_LAT = 0;
	BT_SendCommand("SR,4000\r", false); //Features not correct so set features

	//	U1MODEbits.UARTEN = 0; // disable UART so we can change flow control to none
	//	WaitMs(50);
	//	U1MODEbits.UEN0 = 0; // NO RTS/CTS
	//	U1MODEbits.UEN1 = 0; // NO RTS/CTS
	//	U1MODEbits.UARTEN = 1; // enable UART
	//	U1STA = 0x0400; //Enable transmit

	// assign random mac address
	BT_SendCommand("&R", false);
	WaitMs(100);

	char macAddr[16];
	BT_SendCommand("gds\r", false); // Get mac address
	while (!BT_ReceivePacket(macAddr));

	char message[12];
	macAddr[12] = '\0';
	sprintf(message, "sn,%s_BT\r", &macAddr[8]);

	clear_bt_port();

	BT_SendCommand(message, false); //Set advertise name
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//	BT_SendCommand("sdm,NSA\r", false); //Set model name
	//	if (!BT_CheckResponse(AOK)) {
	//		return false;
	//	}

	//Send "SS" to set default services
	BT_SendCommand("ss,E0\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//Send "SC" for advertisement settings
	BT_SendCommand("sc,2\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	BT_SendCommand("s-,FRC-\r", false); // set serialized name  Bluetooth-friendly name
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// set software version
	BT_SendCommand("sdr,"APP_VERSION_STR"\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// set firmware version
	BT_SendCommand("sdf,"APP_VERSION_STR"\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// set appearance
	BT_SendCommand("sda,0002\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// set serial
	BT_SendCommand("sds,1957\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//  initial connection parameters 
	BT_SendCommand("st,000C,0032,0000,0064\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	if (version_code >= 33) { // public services
		// Public BTLE services and characteristics

		// battery level service with standard 16-bit UUID
		BT_SendCommand("ps,"PUBLIC_BATT_UUID"\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// battery level measurement characteristic
		BT_SendCommand("pc,"PUBLIC_BATT_CHAR_BL",12,04\r", false); //Notify, Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart rate service with standard 16-bit UUID
		BT_SendCommand("ps,"PUBLIC_HR_UUID"\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart rate measurement characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_HRM",12,04\r", false); //Notify, Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart body sensor location characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_BSL",06,01\r", false); //Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// heart rate control point characteristic
		BT_SendCommand("pc,"PUBLIC_HR_CHAR_RCP",06,01\r", false); //Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		//  Automation IO service with standard 16-bit UUID
		BT_SendCommand("ps,"PUBLIC_AIO_UUID"\r", false);
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO digital characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_DIG",16,08,33\r", false); //Notify, Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO analog characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_ANA",16,02,33\r", false); //Notify, Write , Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}

		// Automation IO agg characteristic
		BT_SendCommand("pc,"PUBLIC_AIO_CHAR_AGG",12,0F,33\r", false); //Notify, Read
		if (!BT_CheckResponse(AOK)) {
			return false;
		}
	}

	// Private BTLE services and characteristics

	//Send "ps" to set user defined service UUID
	BT_SendCommand("ps,"PRIVATE_SERVICE",\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom button characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_SWITCHES",22,02\r", false); //Notify, Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom potentiometer characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_POTENTIOMETER",22,02\r", false); //Notify, Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom LED characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_LEDS",0A,04\r", false); //Write , Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom RELAY characteristic with generated UUID
	BT_SendCommand("pc,"PRIVATE_CHAR_RELAYS",0A,04\r", false); //Write , Read
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom analog input characteristic with generated UUID //Write , Read
	BT_SendCommand("pc,"PRIVATE_CHAR_ADC_CHAN",0A,04\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	// Custom digital device characteristic with generated UUID //Write , Read
	BT_SendCommand("pc,"PRIVATE_CHAR_PIC_SLAVE",0A,0F\r", false);
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	BT_SendCommand("wc\r", false); //Command to clear script, just in case there is a script
	if (!BT_CheckResponse(AOK)) {
		return false;
	}

	//Send "R,1" to save changes and reboot
	return BT_RebootEnFlow(false);
}

//**********************************************************************************************************************
// Reboot the module and enable flow control on PIC UART

bool BT_RebootEnFlow(bool do_flow)
{
	bool do_ls = false, good_boot; // causes a mpu serial control lockup if enabled

#ifdef BT_RN4871
	BT_SendCommand("GN\r", false);
	clear_bt_port();
	if (do_ls) {
		BT_SendCommand("LS\r", false); // list services
		WaitMs(4000);
	}
	good_boot = true;
#endif

#ifdef BT_RN4020
	if (do_ls)
		BT_SendCommand("LS\r", false); // list services

	//Send "R,1" to save changes and reboot
	BT_SendCommand("r,1\r", false); //Force reboot
	if (!BT_CheckResponse("Reboot\r\n")) {
		return false;
	}
	//Disable UART while TX line from RN is low during reset and bootup
	StartTimer(TMR_RN_COMMS, 1000);
	U1MODE &= 0x7FFF;
	while (U1RX_PORT) {
		if (TimerDone(TMR_RN_COMMS)) {
			break;
		}
	}
	StartTimer(TMR_RN_COMMS, 4000);
	while (!U1RX_PORT) {
		if (TimerDone(TMR_RN_COMMS)) {
			break;
		}
	}

	UART_RX_IF = 0; //Clear UART Receive interrupt flag
	U1MODE |= 0x8200; //Enable UART, use RTC/CTS flow control
	U1STA |= 0x0400; //Enable transmit

	//Clear out NULL char(s) and other garbage if present after reboot, wait for first char of CMD\r\n response
	StartTimer(TMR_RN_COMMS, 4000);
	while (UART_ReadRxBuffer() != 'C') {
		while (!UART_IsNewRxData()) {
			if (TimerDone(TMR_RN_COMMS)) { //Check if timed out
				return false; //If timed out then return failure
			}
		}
	}

	good_boot = BT_CheckResponse("MD\r\n"); //Check that we received CMD indicating reboot is done


#endif
	//Clear any UART error bits
	U1STAbits.FERR = 0;
	U1STAbits.PERR = 0;
	return good_boot; //Check that we received CMD indicating reboot is done	
}

#ifdef VERIFY_RN_FW_VER
//Retrieve firmware version on module and check against the required version
//Returns true if version is correct; false if not or communication failure

uint16_t BT_CheckFwVer(void)
{
	char fpVer[20];
	char *pfpVer = fpVer;
	char strVer[100];
	char *pstrVer = strVer;
	uint16_t verMajor,
		verMinor,
		verPatch;

	//flush UART RX buffer just in case there's old data
	while (UART_IsNewRxData()) { //While buffer contains old data
		UART_ReadRxBuffer(); //Keep reading until empty
		WaitMs(100);
	}

	StartTimer(TMR_RN_COMMS, 2000);
	BT_SendCommand("v\r", false); // Get firmware version
	while (!BT_ReceivePacket(strVer)) {
		if (TimerDone(TMR_RN_COMMS)) {
			return false;
		}
	}

	//Skip to first digit
	while ((*pstrVer < '0' || *pstrVer > '9') && *pstrVer != NULL) {
		pstrVer++;
	}
	//Extract version number
	while ((*pstrVer >= '0' && *pstrVer <= '9') || *pstrVer == '.') {
		*pfpVer = *pstrVer;
		pfpVer++;
		pstrVer++;
	}
	*pfpVer = '\0';

	//Tokenize and convert to unsigned
	sscanf(fpVer, "%u.%u.%u", &verMajor, &verMinor, &verPatch);

	//Verify version number
	if ((verMajor != RN_FW_VER_MAJOR133) && (verMajor != RN_FW_VER_MAJOR)) {
		return false;
	}
	if ((verMinor != RN_FW_VER_MINOR133) && (verMinor != RN_FW_VER_MINOR)) {
		return false;
	}
	if ((verPatch != RN_FW_VER_PATCH133) && (verPatch != RN_FW_VER_PATCH)) {
		return false;
	}

	return verMinor;
}
#endif //VERIFY_RN_FW_VER
