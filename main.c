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
 * File:        main.c
 * Date:        July 24, 2014
 * Compiler:    XC16 v1.23
 * 
 * Remote Relay mods Oct 2016 FGB@MCHP
 * 
 * 	// RELAYs are outputs and open-drain
	// to drive ILQ2 opto
	// setup in Mikrobus header
	ODCDbits.ODD3 = 1; // pin 16 PWM
	ODCDbits.ODD9 = 1; // pin 11 SDA
	ODCDbits.ODD10 = 1; // pin 12 SCL
	ODCDbits.ODD4 = 1; // pin 2 RST
 *
 */

#include <xc.h>
#include <stdint.h>
#include "app.h"
#include "config.h"

void initBoard(void);

// PIC24FV16KM202 Configuration Bit Settings

// 'C' source line config statements

// FBS

#pragma config BWRP = OFF               // Boot Segment Write Protect (Disabled)
#pragma config BSS = OFF                // Boot segment Protect (No boot program flash segment)

// FGS
#pragma config GWRP = OFF               // General Segment Write Protect (General segment may be written)
#pragma config GCP = OFF                // General Segment Code Protect (No Protection)

// FOSCSEL
#pragma config FNOSC = FRC              // Oscillator Select (Fast RC Oscillator (FRC))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Analog Mode for use with crystal)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = OFF                // Internal External Switch Over bit (Internal External Switchover mode enabled (Two-speed Start-up enabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = CLKO          // CLKO Enable Configuration bit (CLKO output signal enabled)
#pragma config POSCFREQ = HS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency greater than 8MHz)
#pragma config SOSCSEL = SOSCHP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for high-power operation)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Standard WDT selected(windowed WDT disabled))

// FPOR
#pragma config BOREN = BOR0             // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware, SBOREN bit disabled)
#pragma config RETCFG = OFF             //  (Retention regulator is not available)
#pragma config PWRTEN = ON              // Power-up Timer Enable bit (PWRT enabled)
#pragma config I2C1SEL = SEC            // Alternate I2C1 Pin Mapping bit (Use  Alternate ASCL1/ASDA1 Pins For I2C1)
#pragma config BORV = V18               // Brown-out Reset Voltage bits (Brown-out Reset set to lowest voltage (1.8V))
#pragma config MCLRE = ON               // MCLR Pin Enable bit (RA5 input pin disabled, MCLR pin enabled)

// FICD
#pragma config ICS = PGx1               // ICD Pin Placement Select bits (EMUC/EMUD share PGC1/PGD1)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//**********************************************************************************************************************
// Main routine - start of executable code

int main(void)
{
	initBoard(); //Initialize the pins and peripherals

	while (1) {
		APP_Tasks();
		Idle(); //Idle until an interrupt is generated
		RCONbits.IDLE = 0;
		LED2 = !LED2;
	}

	//End of while(1) main loop
	return(true);
}

//**********************************************************************************************************************
// Initialize the pins and peripherals

void initBoard(void)
{
	/****************************************************************************
	 * Oscillator Init
	 * Clocking is setup at 32MHz sys clock and to allow USB functionality
	 * Self-tune on SOF is enabled if USB is enabled and connected to host
	 ***************************************************************************/
	// DOZEN disabled; DOZE 1:16; CPDIV 1:1; RCDIV FRC/1; PLLEN disabled; ROI disabled;
	CLKDIVbits.RCDIV = 1;
	OSCCONbits.COSC = 0x1;
	OSCCONbits.NOSC = 0x1;

	// STSRC USB; STEN enabled; STOR disabled; STORPOL Interrupt when STOR is 1; STLOCK disabled; STLPOL Interrupt when STLOCK is 1; STSIDL disabled; TUN Center frequency; 
	OSCTUN = 0x0;

	//Enable low voltage retention sleep mode
	RCONbits.RETEN = 1;

#ifdef SET_PMD_BITS    //see config.h, Application settings section
	/****************************************************************************
	 * PMD bits - setting a bit disables clocking to that peripheral
	 * (drops operating current by about 2 mA when used in this app)
	 ***************************************************************************/
	PMD1bits.T4MD = 1;

#if !defined (USE_SLEEP) || defined (SLEEP_MODE_RTCC)    //see config.h, Application settings section
	PMD1bits.T1MD = 1;
#endif

	PMD1bits.I2C1MD = 1;
	PMD1bits.U2MD = 1;
	PMD1bits.SPI2MD = 1;
	PMD1bits.SPI1MD = 1;
	PMD3bits.TXMMD = 1;

#if !defined (USE_SLEEP) || !defined (SLEEP_MODE_RTCC)    //see config.h, Application settings section
	PMD3bits.RTCCMD = 1;
#endif

	PMD3bits.PMPMD = 1;
	PMD3bits.CRCMD = 1;
	PMD3bits.DAC1MD = 1;
	PMD3bits.U3MD = 1;
	PMD3bits.I2C2MD = 1;
	PMD2 = 0xFFFF;
	PMD4bits.UPWMMD = 1;
	PMD4bits.U4MD = 1;
	PMD4bits.REFOMD = 1;
	PMD4bits.CTMUMD = 1;
	PMD4bits.HLVDMD = 1;
	PMD5 = 0xFFFF;
	PMD6 = 0xFFFF;
	PMD7 = 0xFFFF;
#endif

	/****************************************************************************
	 * GPIO Init
	 ***************************************************************************/
	ANSA = 0x00;
	ANSB = 0x00;


	CNPU1 = 0;
	CNPU2 = 0;


	CNPD1 = 0;
	CNPD2 = 0;


	CNEN1 = 0x0000;
	CNEN2 = 0x0000;

	ODCB = 0x0000;

	IEC1bits.CNIE = 1;

	// RELAYs are outputs and open-drain
	// to drive ILQ2 opto
	// setup in Mikrobus header
	//	ODCDbits.ODD3 = 1; // pin 16
	//	ODCDbits.ODD9 = 1; // pin 11
	//	ODCDbits.ODD10 = 1; // pin 12
	//	ODCDbits.ODD4 = 1; // pin 2

	// LEDs are outputs and off
	LED1 = 1;
	LED2 = 0;
	LED3 = 0;
	LED4 = 0;
	LED5 = 0;
	LED6 = 0;
	LED7 = 0;
	LED_TRIS1 = 0;
	LED_TRIS2 = 0;
	LED_TRIS3 = 0;
	LED_TRIS4 = 0;

	//RN4020 module - UART1
	BT_WAKE_HW = 1; //Dormant line is set high
	BT_WAKE_HW_TRIS = 0; //Dormant line is output

	BT_WAKE_SW = 0; //keep low until after UART is initialized
	BT_WAKE_SW_TRIS = 0;

	BT_CMD = 0; //Command mode on
	BT_CMD_TRIS = 0;

	BT_WS_TRIS = 1;
	BT_MLDP_EV_TRIS = 1;
	BT_CONNECTED_TRIS = 1;

	U1CTS_TRIS = 1;
	U1RX_TRIS = 1;
	U1RTS_LAT = 0;
	U1RTS_TRIS = 0;
	U1TX_TRIS = 0;

	/****************************************************************************
	 * PPS Init - Peripheral Pin Select
	 * Click Boards using PPS-controlled peripherals will require additional
	 * setup here
	 ***************************************************************************/
	__builtin_disi(0x3FFF); //disable interrupts

	//unlock registers
	__builtin_write_OSCCONL(OSCCON & 0xBF);

	__builtin_write_OSCCONL(OSCCON | 0x40);

	__builtin_disi(0); //enable interrupts

	/****************************************************************************
	 * Interrupt Priorities
	 * Interrupt-enabled peripherals being used for Click Boards should be
	 * configured here as well
	 ***************************************************************************/
	//    UERI: U1E - UART1 Error
	//    Priority: 6
	IPC16bits.U1ERIP = 6;

	//    UTXI: U1TX - UART1 Transmitter
	//    Priority: 5
	IPC3bits.U1TXIP = 5;

	//    URXI: U1RX - UART1 Receiver
	//    Priority: 5
	IPC2bits.U1RXIP = 5;


	//    TI: T1 - Timer1
	//    Priority: 3
	IPC0bits.T1IP = 3;

	//    RTCI: RTCC - Real-Time Clock and Calendar
	//    Priority: 2
	IPC15bits.RTCIP = 2;

	//    CN: Switches - change notification
	//    Priority: 2
	IPC4bits.CNIP = 2;

	//    ADI: ADC1 - Pipeline A/D Converter 1
	//    Priority: 1
	IPC3bits.AD1IP = 1;
}
