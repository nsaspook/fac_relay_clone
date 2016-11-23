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
#include "packet.h"
#include "adc.h"
#include "leds.h"
#include "switches.h"
#include "comparator.h"
#include "rtcc.h"
#include "sleep.h"
#include "spi.h"
#include "dac.h"
#include "../link.h"

APP_DATA appData;

//Primary application state machine

void APP_Tasks(void)
{
	//Update LED outputs
	LED_Tasks();

	//Time to check battery/input voltage?
	if (TimerDone(TMR_BAT_CHECK) && appData.state != APP_INITIALIZE) {
		StartTimer(TMR_BAT_CHECK, CMP_Tasks()); //Run tasks and restart timer
	}

	switch (appData.state) {
		//Initial state
	case APP_INITIALIZE:
		if (APP_Initialize()) {
			appData.state = APP_RUNNING;
		} else {
			appData.state = APP_INITIALIZATION_ERROR;
		}
		break;

		//Initialization failed
	case APP_INITIALIZATION_ERROR:
		LED_SET_LightShow(LED_ERROR);
		break;

	case APP_RUNNING:
		LED_SET_LightShow(SLAVE_RUNNING);
		//Check if switches have changed and debounce timers are expired
		Switch_Tasks();
		if (appData.sendSwitches) { //New switch status to send?
			appData.sendSwitches = false;
		}

		appData.got_packet = SPI_ReceivePacket(appData.receive_packet);
		if (appData.got_packet == true) { //true if new packet received
			appData.packet_data = Read_Link_Packet(appData.receive_packet);
			SPI_ClearBufs();
			SPI_WriteDacBuffer(appData.packet_data->dac1, 1);
			SPI_WriteDacBuffer(appData.packet_data->dac2, 2);
			appData.blink_rate = LED_BLINK_MS_FAST;
			appData.packet_data->io1 = 0xde;
			appData.packet_data->io2 = 0xad;
			appData.packet_data->eof = SPI_CHECKMARK;
			Write_Link_Packet((const uint8_t *) appData.packet_data + 1, false);
		}
		break;

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
	appData.blink_rate = LED_BLINK_MS;
	appData.packet_size = LINK_BYTES; // set to data structure size

	/****************************************************************************
	 * Peripherals Init
	 ***************************************************************************/
	UART_Init(); //Initialize the UART
	Timers_Init(); //Initialize the timers
	SPI_Init();
	DAC_Init();

	SLED = 1; // init completed
	return true;
}
