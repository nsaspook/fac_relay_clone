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
 * Date:        Oct 27, 2016
 * Compiler:    XC16 v1.26
 * 
 * Remote Relay mods Oct 2016 FGB@MCHP
 * ported to PIC24FV 
 * Version updates
 * V2.1 DFU OTA mode added, input port shared with relay #4 output
 *
 */

#include <xc.h>
#include <stdint.h>
#include "app.h"
#include "config.h"
#include "spi.h"
#include "timers.h"

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
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with Postscaler and PLL Module (FRCDIV+PLL))
#pragma config SOSCSRC = DIG            // SOSC Source Type (Digital Mode for use with external source)
#pragma config LPRCSEL = HP             // LPRC Oscillator Power and Accuracy (High Power, High Accuracy Mode)
#pragma config IESO = OFF               // Internal External Switch Over bit (Internal External Switchover mode disabled (Two-speed Start-up disabled))

// FOSC
#pragma config POSCMOD = NONE           // Primary Oscillator Configuration bits (Primary oscillator disabled)
#pragma config OSCIOFNC = IO            // CLKO Enable Configuration bit (Port I/O enabled (CLKO disabled))
#pragma config POSCFREQ = LS            // Primary Oscillator Frequency Range Configuration bits (Primary oscillator/external clock input frequency less than 100kHz)
#pragma config SOSCSEL = SOSCLP         // SOSC Power Selection Configuration bits (Secondary Oscillator configured for low-power operation)
#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Both Clock Switching and Fail-safe Clock Monitor are enabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscale Select bits (1:32768)
#pragma config FWPSA = PR128            // WDT Prescaler bit (WDT prescaler ratio of 1:128)
#pragma config FWDTEN = ON              // Watchdog Timer Enable bits (WDT enabled in hardware)
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
		ClrWdt();
	}

	//End of while(1) main loop
	return(true);
}

//**********************************************************************************************************************
// Initialize the pins and peripherals

void initBoard(void)
{ /****************************************************************************
	 * Oscillator Init
	 * Clocking is setup at 32MHz sys clock and to allow USB functionality
	 * Self-tune on SOF is enabled if USB is enabled and connected to host
	 ***************************************************************************/
	// DOZEN disabled; DOZE 1:16; CPDIV 1:1; RCDIV FRC/1; PLLEN disabled; ROI disabled;
	CLKDIVbits.RCDIV = 0;
	OSCCONbits.COSC = 0x1;
	OSCCONbits.NOSC = 0x1;

	// STSRC USB; STEN enabled; STOR disabled; STORPOL Interrupt when STOR is 1; STLOCK disabled; STLPOL Interrupt when STLOCK is 1; STSIDL disabled; TUN Center frequency; 
	OSCTUN = 0x0;

	//Enable low voltage retention sleep mode
	RCONbits.RETEN = 1;

	RCONbits.SWDTEN = 0;

	/****************************************************************************
	 * GPIO Init
	 ***************************************************************************/
	ANSA = 0x00;
	ANSB = 0x00;
	ANSBbits.ANSB3 = 1;
	ANSBbits.ANSB15 = 1;

	CNPU1 = 0;
	CNPU2 = 0;

	CNPD1 = 0;
	CNPD2 = 0;

	CNEN1 = 0x0000;
	CNEN2 = 0x0000;

	ODCB = 0x0000;

	//	IEC1bits.CNIE = 1;

	// LEDs are outputs and off
	SLED = 0;
	SLED_TRIS = 0;

	U1CTS_TRIS = 1;
	U1RX_TRIS = 1;
	U1RTS_LAT = 0;
	U1RTS_TRIS = 0;
	U1TX_TRIS = 0;

	/* SPI2 HW setup */
	SSP2CON1bits.SSPM = 4; // SPI slave
	SSP2CON1bits.CKP = 0; // SCK polarity mode 0,0
	SSP2STATbits.CKE = 0; // SCK select 
	SSP2STATbits.SMP = 0; // sample mid
	SSP2CON1bits.SSPEN = 1; // enable spi ports
	PADCFG1bits.SCK2DIS = 0;
	PADCFG1bits.SDA2DIS = 0;

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

	// SPI
	// error
	IPC12bits.BCL2IP = 6;
	// spi_buf
	IPC12bits.SSP2IP = 5;

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
