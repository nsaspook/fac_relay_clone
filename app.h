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

#ifndef APP_H
#define APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "link.h"

#define ERROR_NONE              1
#define ERROR_INITIALIZATION    -2
#define ERROR_RN_FW             -3

typedef enum {
	APP_INITIALIZE = 0, // Initialize application
	APP_INITIALIZATION_ERROR, // Initialization Error
	APP_BLUETOOTH_ADVERTISE, // Advertise the bluetooth connection, not connected
	APP_BLUETOOTH_PAIRED, // Bluetooth module is paired to server, we idle
	APP_SLEEP // Sleep mode
} APP_STATE_T;

typedef struct {
	APP_STATE_T state; //APP_Tasks state
	char receive_packet[BT_RX_PKT_SZ]; //message buffers
	char transmit_packet[BT_TX_PKT_SZ];
	bool got_packet, //new packet flag
	update_packet,
	sendSwitches, //new switch states ready to send
	ADCcalFlag, //ADC is calibrated if true
	led1, led2, led3, led4, led5, led6, //LED states
	oled1, oled2, oled3, oled4,
	rn4871_connected,rn_4871_packets;
	int8_t error_code;
	volatile bool sw1, sw2, sw3, sw4, //switch states
	sw1Changed, sw2Changed, sw3Changed, sw4Changed, //switch state has changed
	RTCCalarm, //RTCC alarm has tripped
	accumReady, //ADC accumulator is done
	ADCinUse, //ADC or accumulator register is currently in use
	timer1Flag, //Timer1 has tripped
	CNint, //CN interrupt has tripped (flag to exit sleep)
	sleepFlag; //sleep mode triggered
	uint16_t potValue, potValueOld, potValueLastTX, version_code, hrmEnergy; //potentiometer values - current, previous, and last transmitted, firmware version
	struct LINK_DATA *packet_data;
} APP_DATA;

/* for 24-bit transmit and extra status data */
typedef struct A_data {
	uint32_t dummy12 : 12; // dummy space for adc data
	uint32_t nullbits : 2;
	uint32_t index : 3; //adc channel select
	uint32_t single_diff : 1;
	uint32_t start_bit : 1;
	uint32_t dummy8 : 8;
	uint32_t finish : 1;
	uint32_t in_progress : 1;
} A_data;

/* upper-> lower bytes to 32 bit word for ADC/DAC, etc ... */
union bytes4 {
	uint32_t ld;
	uint8_t bd[4];
};

/* upper/lower bytes to 16 bit word for ADC/DAC, etc ... */
union bytes2 {
	uint16_t ld;
	uint8_t bd[2];
};

/* used to hold 24-bit adc buffer, index and control bits */
union adc_buf_type {
	uint32_t ld;
	uint8_t bd[4];
	struct A_data map;
};

typedef struct {
	union adc_buf_type mcp3208_cmd;
	uint16_t potValue;
	uint8_t chan;
} ADC_DATA;

void APP_Tasks(void);
bool APP_Initialize(void);

#endif //APP_H
