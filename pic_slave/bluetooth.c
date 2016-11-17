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

uint16_t BT_CheckFwVer(void);

//**********************************************************************************************************************
// Receive a message over the Bluetooth link

bool BT_ReceivePacket(char * Message)
{
	return false;
}

//**********************************************************************************************************************
// Send a command to the RN4020 module
//Return true for success, false for busy

bool BT_SendCommand(const char *data, bool wait)
{
	return false;
}

//**********************************************************************************************************************
// Send a byte to the RN4020 module

void BT_SendByte(char data)
{

}

//**********************************************************************************************************************
// Get a response from the RN4020 module

bool BT_GetResponse(char *data)
{
	return false;
}

//**********************************************************************************************************************
// Compare the buffer with the response with one of the expected responses

bool BT_CompareResponse(const char *data1, const char *data2)
{
	return false; //Did not reach end of string so return failure
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response

bool BT_CheckResponse(const char *data)
{

	return true; //All bytes matched so return success
}

//**********************************************************************************************************************
// Get a response from the RN4020 module and compare with an expected response
//   All incoming bytes in the position of the wildcard character are ignored
//   Use this to ignore text that changes, like MAC addresses.

bool BT_CheckResponseWithWildcard(const char *data, char Wildcard)
{

	return true; //All bytes matched or were ignored so return success
}

//**********************************************************************************************************************
// Set up the RN4020 module

bool BT_SetupModule(void)
{
	//Send "R,1" to save changes and reboot
	return true;
}

//**********************************************************************************************************************
// Reboot the module and enable flow control on PIC UART

bool BT_RebootEnFlow(void)
{
	return true; //Check that we received CMD indicating reboot is done	
}

#ifdef VERIFY_RN_FW_VER
//Retrieve firmware version on module and check against the required version
//Returns true if version is correct; false if not or communication failure

uint16_t BT_CheckFwVer(void)
{
	return true;
}
#endif //VERIFY_RN_FW_VER
