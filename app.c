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
 * File:        app.c
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.23
 *
 */

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "config.h"
#include "timers.h"
#include "uart.h"
#include "bluetooth.h"
#include "adc.h"
#include "leds.h"
#include "switches.h"
#include "rtcc.h"
#include "sleep.h"
#include "spi.h"
#include "link.h"
#include "automio.h"

APP_DATA appData;
ADC_DATA adcData;
AIO_DATA aioData;

//Primary application state machine

void APP_Tasks(void)
{
	static uint16_t failure = 0;
#ifdef USE_SLEEP                //see config.h, Application setting section
	APP_STATE_T savedState;
	int16_t potDiff;

	//Has inactivity timer expired?
	if (appData.sleepFlag) {
		savedState = appData.state; //Save context
		appData.state = APP_SLEEP; //Enter sleep state
	}
#endif

	//Update LED outputs
	LED_Tasks();

	switch (appData.state) {
		//Initial state
	case APP_INITIALIZE:
		if (APP_Initialize()) {
			appData.state = APP_BLUETOOTH_ADVERTISE;
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;

		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		LED_SET_LightShow(LED_ERROR);
		break;

		//We're not connected to a device - advertise mode
	case APP_BLUETOOTH_ADVERTISE:
		LED_SET_LightShow(LED_BTLE_ADVERTISING);

#ifdef	BT_RN4871
		appData.rn_4871_packets = true;
		appData.got_packet = BT_ReceivePacket(appData.receive_packet); // check for RN4871 connect packet
		if (appData.got_packet == true) { //true if new packet received
			// rn4871 connection status packets
			if (strstr(appData.receive_packet, "CONNECT,")) {
				appData.rn4871_connected = true;
			}
			appData.got_packet = false;
		}
#endif

		if (BT_CONNECTED || appData.rn4871_connected) {
			appData.state = APP_BLUETOOTH_PAIRED;
		}
		break;

		//We are connected to a BTLE device
	case APP_BLUETOOTH_PAIRED:
		//Update LEDs
		LED_SET_LightShow(LED_BTLE_PAIRED);
		//Check to see if we are still connected; return to advertise state if not
		if (!BT_CONNECTED && !appData.rn4871_connected) {
			appData.update_packet = false;
			LED_SET_LightShow(LED_BTLE_ADVERTISING);
			appData.state = APP_BLUETOOTH_ADVERTISE;
			break;
		}

		//Check if switches have changed and debounce timers are expired
		Switch_Tasks();
		if (appData.sendSwitches) { //New switch status to send?
			//Form message
			sprintf(appData.transmit_packet, "shw,"PRIVATE_CHAR_SWITCHES_H",%d%d%d%d\r", appData.sw1, appData.sw2, appData.sw3, appData.sw4);
			//Try to transmit the message; reset flag if successful
			if (BT_SendCommand(appData.transmit_packet, true)) {
				BT_CheckResponse_AOK(&failure);
				appData.sendSwitches = false;
			}
		}

		//Process ADC accumulator value if oversampling is complete
		if (appData.accumReady) {
			ADC_ProcAccum();
#ifdef USE_SLEEP                //see config.h, Application setting section
			potDiff = appData.potValue - appData.potValueOld; //Reset the inactivity sleep timer if pot has changed
			if (potDiff > POT_KEEP_AWAKE_DELTA || potDiff < -POT_KEEP_AWAKE_DELTA) {
				SleepTimerReset();
			}
#endif
			appData.accumReady = false; //Clear app flags
			appData.ADCinUse = false;
		}

		// packet transmission queue, TimerDone puts packet in the transmission stream

		//Start new ADC read if timer expired, not currently sampling, and not waiting to process accumulator
		if (TimerDone(TMR_ADC) && appData.ADCinUse == false) {
			if (ADC_Tasks()) {
				StartTimer(TMR_ADC, ADC_REFRESH_MS);
			} //Restart timer once module is up and running
		}

		//Transmit new potentiometer reading?
		if (TimerDone(TMR_POT)) {
			//Send message only if pot value has changed
			if (appData.potValue != appData.potValueLastTX) {
				//Form message
				sprintf(appData.transmit_packet, "shw,"PRIVATE_CHAR_POTENTIOMETER_H",%04d\r", appData.potValue);
				//Try to transmit the message; reset timer if successful
				if (BT_SendCommand(appData.transmit_packet, true)) {
					appData.potValueLastTX = appData.potValue;
					StartTimer(TMR_POT, POT_TX_MS);
				}
			} else {
				StartTimer(TMR_POT, POT_TX_MS);
			} //value not changed - skip this transmission
		}

		if (TimerDone(TMR_BATT)) {
			//Form message
			sprintf(appData.transmit_packet, "shw,"PUBLIC_BATT_CHAR_H",%02d\r\n", (appData.potValue >> 6)&0b00111111);
			//Try to transmit the message; reset timer if successful
			if (BT_SendCommand(appData.transmit_packet, true)) {
				BT_CheckResponse_AOK(&failure);
				StartTimer(TMR_BATT, BATT_TX_MS);
			}
		}

		if (TimerDone(TMR_HR)) {
			//Form message
			sprintf(appData.transmit_packet, "shw,"PUBLIC_HR_CHAR_HRM_H",%02x%02x%02x%02x\r\n", 0x08, (appData.potValue >> 4)&0xff, appData.hrmEnergy & 0x00ff, appData.hrmEnergy >> 8); // format mask and ADC data
			//Try to transmit the message; reset timer if successful
			if (BT_SendCommand(appData.transmit_packet, true)) {
				BT_CheckResponse_AOK(&failure);
				StartTimer(TMR_HR, HR_TX_MS);
				sprintf(appData.transmit_packet, "shw,"PUBLIC_HR_CHAR_BSL_H",%02x\r\n", 3);
				BT_SendCommand(appData.transmit_packet, false);
				appData.hrmEnergy++;
			}
		}

		if (TimerDone(TMR_AIO_DIG)) {
			//Form message
			sprintf(appData.transmit_packet, "shw,"PUBLIC_AIO_CHAR_DIG_H",0101010101010101\r\n"); // digital data
			//Try to transmit the message; reset timer if successful
			if (BT_SendCommand(appData.transmit_packet, true)) {
				BT_CheckResponse_AOK(&failure);
				StartTimer(TMR_AIO_DIG, AIO_TX_MS);
			}
		}

		//Process any new messages received from RN module
#ifdef	BT_RN4871
		appData.rn_4871_packets = true;
#endif
		appData.got_packet = BT_ReceivePacket(appData.receive_packet); //Get new message if one has been received from the RNxxxx
		if (appData.got_packet == true) { //true if new packet received

			appData.packet_data = Get_Link_Packet();
			appData.packet_data->dac1 = appData.potValue & 0xff;
			appData.packet_data->dac2 = appData.potValue >> 8;
			Write_Link_Packet((uint8_t *) appData.packet_data, true);

			if (strstr(appData.receive_packet, "WV,001E,")) { //Check for LED update message 1.23
				GetNewLEDs(strstr(appData.receive_packet, "WV,001E,")); //Latch new LED values
				appData.update_packet = true;
			}
			if (strstr(appData.receive_packet, "WV,"PRIVATE_CHAR_LEDS_H",")) { //Check for LED update message 1.33
				GetNewLEDs(strstr(appData.receive_packet, "WV,"PRIVATE_CHAR_LEDS_H",")); //Latch new LED values
				appData.update_packet = true;
			}
			//
			//Other message handling can be added here
			//
			//receive new SPI ADC channel
			if (strstr(appData.receive_packet, "WV,"PRIVATE_CHAR_ADC_CHAN_H",")) {
				GetNewADC_Chan(strstr(appData.receive_packet, "WV,"PRIVATE_CHAR_ADC_CHAN_H",")); // new ADC config data
			}
			//receive new SPI SLAVE request
			if (strstr(appData.receive_packet, "WV,"PRIVATE_CHAR_PIC_SLAVE_H",")) {

			}
			// HRM energy expended reset
			if (strstr(appData.receive_packet, "WV,"PUBLIC_HR_CHAR_RCP_H",01")) {
				appData.hrmEnergy = 0;
			}
			//receive new BATTERY request
			if (strstr(appData.receive_packet, "RV,"PUBLIC_BATT_CHAR_H"")) {
				//Form message
				sprintf(appData.transmit_packet, "shw,"PUBLIC_BATT_CHAR_H",%d\r", 63);
				//Try to transmit the message; reset timer if successful
				BT_SendCommand(appData.transmit_packet, false);
				BT_CheckResponse_AOK(&failure);
			}

#ifdef	BT_RN4871

			if (strstr(appData.receive_packet, "DISCONNECT") || (failure > 25)) {
				appData.rn4871_connected = false;
				failure = 0;
			}
#endif
		}
		break;

#ifdef USE_SLEEP                //see config.h, Application setting section        
		//Put micro and RN module to sleep - any button press will cause wake up
	case APP_SLEEP:
		appData.sleepFlag = 0; //clear flag and call sleep function
		APP_SleepNow();
		appData.state = savedState; //Woken from sleep; restore state

		break;
#endif //USE_SLEEP

	default:
		break;
	} //end switch(appData.state)
} //end APP_Tasks()

//Sets up the RN module

bool APP_Initialize(void)
{
	/****************************************************************************
	 * Initialize appData structure
	 ***************************************************************************/
	appData.error_code = ERROR_NONE;
	appData.got_packet = false;
	appData.potValue = 0;
	appData.potValueOld = 0xFFFF;
	appData.potValueLastTX = 0xFFFF;
	appData.state = APP_INITIALIZE;
	appData.sw1 = false;
	appData.sw2 = false;
	appData.sw3 = false;
	appData.sw4 = false;
	appData.led1 = 0;
	appData.led2 = 0;
	appData.led3 = 0;
	appData.led4 = 0;
	appData.led5 = 0;
	appData.led6 = 0;
	appData.update_packet = true;
	appData.sw1Changed = false;
	appData.sw2Changed = false;
	appData.sw3Changed = false;
	appData.sw4Changed = false;
	appData.sendSwitches = false;
	appData.ADCcalFlag = false;
	appData.sleepFlag = false;
	appData.RTCCalarm = false;
	appData.accumReady = false;
	appData.ADCinUse = false;
	appData.timer1Flag = false;
	appData.rn4871_connected = false;
	appData.rn_4871_packets = false;

	/****************************************************************************
	 * Peripherals Init
	 ***************************************************************************/
	ADC_Init(); //Initialize the pADC
	UART_Init(); //Initialize the UART
	Timers_Init(); //Initialize the timers
	SPI_Init();

#ifdef USE_SLEEP            //see config.h, Application settings section
#ifdef SLEEP_MODE_RTCC
	RTCC_Init();
#endif  //SLEEP_MODE_RTCC
#endif  //USE_SLEEP

	// set RN4871 to command mode
#ifdef BT_RN4871
	U1MODEbits.UARTEN = 0; // disable UART so we can change flow control to none
	WaitMs(50);
	U1MODEbits.UEN0 = 0; // NO RTS/CTS
	U1MODEbits.UEN1 = 0; // NO RTS/CTS
	U1MODEbits.UARTEN = 1; // enable UART
	U1STA = 0x0400; //Enable transmit

	// BTCMD("$");
	BT_SendCommand("$", false);
	WaitMs(100);
	// BTCMD("$$$");
	BT_SendCommand("$$$", false);
	WaitMs(500);

	//Module is now in command mode and ready for input
	if (!BT_SetupModule_4871()) { //Setup RN4871 module
		appData.error_code = ERROR_INITIALIZATION;
		return false;
	}
#endif

#ifdef	BT_RN4020
	BT_WAKE_SW = 1; //wake module
	//Wait for WS status high
	StartTimer(TMR_RN_COMMS, 4000); //Start 4s timeout
	while (BT_WS == 0) {
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
		{
			appData.error_code = ERROR_INITIALIZATION;
			return false;
		}
	}

	//Wait for end of "CMD\r\n" - we don't check for full "CMD\r\n" string because we may 
	//miss some bits or bytes at the beginning while the UART starts up
	StartTimer(TMR_RN_COMMS, 4000); //Start 4s timeout
	while (UART_ReadRxBuffer() != '\n') {
		if (TimerDone(TMR_RN_COMMS)) //Check if timed out
		{
			appData.error_code = ERROR_INITIALIZATION;
			return false;
		}
	}

	//Module is now in command mode and ready for input
	if (!BT_SetupModule_4020()) { //Setup RN4020 module
		appData.error_code = ERROR_INITIALIZATION;
		return false;
	}

#ifdef VERIFY_RN_FW_VER
	//Verify RN4020 module's firmware version
	if (!(appData.version_code = BT_CheckFwVer())) {
		appData.error_code = ERROR_RN_FW;
		return false;
	}
#endif // VERIFY_RN_FW_VER 
#endif

	//flush UART RX buffer as a precaution before starting app state machine
	clear_bt_port();

	SLED = 1; // init completed
	return true;
}
