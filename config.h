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
 * File:        config.h
 * Date:        January 20, 2015
 * Compiler:    XC16 v1.23
 *
 * General definitions for the project
 * 
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <xc.h>

#define APP_VERSION_STR "2.7"       //This firmware version

/*******************************************************************************
 * Application settings - these will change application behavior
 ******************************************************************************/

//Selectively set PMD bits if this is defined
//Disables clocking to peripherals that are not used in this demo code
//Reduces operating current by about 2 mA
//Risk is trying to add code that uses a disabled peripheral and
//forgetting that it is disabled by PMD
//The bits are selectively set in main.c --> initBoard()
//#define SET_PMD_BITS

//Enables sleep mode based on an inactivity timer.
//Switch presses and potentiometer changes will reset inactivity timer window.
//D6 will go solid on when device first goes to sleep and then will
//pulse periodically during sleep.
//Any switch press will wake device from sleep.
//Reduces power consumption but might not be wanted, depending on use case
//Sleep mode will be enabled when this is defined
//Inactivity time-out is set below in Application timers section
//#define USE_SLEEP

//Determines mode of sleep operation, to illustrate different possible methods.
//When defined, sleep mode will clock switch to the LPRC for the system clock
//and will use the RTCC (clocked by LPRC) for periodic wake-up to flash the status LED.
//If not defined, sleep mode will use Timer 1 (clocked by LPRC) for periodic wakeup
//to flash the status LED. Each mode has its strengths.
//If timing accuracy is required using RTCC mode, the RTCC should be clocked
//from the external crystal on SOSC instead.
//Setting has no effect if USE_SLEEP is not defined.
//#define SLEEP_MODE_RTCC

//A change in potentiometer reading greater than this will reset the sleep inactivity timer
//A threshold greater than 1 prevents potentiometer noise / ADC drift from keeping board awake
//Has no effect if sleep is disabled
#define POT_KEEP_AWAKE_DELTA    5               //ADC count delta after oversampling, averaging, and 10-bit conversion

//Enable / Disable the MCP1642B 5V boost power supply for 5V power pin on MikroBUS header
//Set to 0 to disable; 1 to enable (Enable this for 5V Click Boards)

//*!*!*!*!*!*!*!*!*!*!*!*!*   NOTE   *!*!*!*!*!*!*!*!*!*!*!*!*
//If using a 5V Click Board with analog output, also set S7 on the PCB to the "5V"
//setting to enable the analog voltage divider which will scale the output to 0 - 3.3V
//#define MCP1642B_EN    0
#define MCP1642B_EN    1

// UART baud rate - RN module defaults to 115200
#define BRG_115200 (FCY/(4*115200) - 1)        //BRG value for 115,200 baud with BRGH = 1 (with rounding)

//Comparator voltage reference CVR setting
#define CVR_BITS            18                 //Determines base voltage threshold for low battery indication

//Number of samples to average for potentiometer ADC reading, in addition to hardware oversampling
#define ADC_NUM_AVGS        5

//If defined, the RN4020's firmware version will be checked as part of initialization.
//If the version is not equal to the version specified below, the board will
//error out with the initialization error code display and not operate
#define VERIFY_RN_FW_VER
#define RN_FW_VER_MAJOR     1           //Require 1.23.5
#define RN_FW_VER_MINOR     23          //These values can be changed as needed
#define RN_FW_VER_PATCH     5

#define RN_FW_VER_MAJOR133     1 
#define RN_FW_VER_MINOR133     33 
#define RN_FW_VER_PATCH133     4

//Application timers
#define SLEEP_TIME          TIMER_5MIN_PERIOD_PS256     //inactivity timer for sleep - applies only when USE_SLEEP is defined
#define DEBOUNCE_MS         75          //debounce time for switches 1 - 4
#define ADC_REFRESH_MS      50          //delay between ADC reads
#define POT_TX_MS           500         //delay between transmitting new pot values
#define LED_BLINK_MS        900         //LED blink rate for advertise mode
#define BT_TX_MS            150         //minimum time between consecutive BTLE message transmissions
#define BAT_CHK_DELAY_MS    30000       //delay between input voltage checks
#define BAT_CHK_WAIT_MS     10          //CVref & CMP stabilization time
//Periods for timer 1 sleep mode (for periodic sleep wakeup); 31KHz LPRC; 1:256 prescale
#define T1_WAKE_PERIOD      2       //2 ~= 16 ms
#define T1_SLEEP_PERIOD     605     //605 ~= 5 seconds

//Buffer sizes
#define SIZE_RxBuffer   256               //UART RX software buffer size in bytes
#define SIZE_TxBuffer   256               //UART TX software buffer size in bytes
#define SIZE_SPI_Buffer 64

#define BT_RX_PKT_SZ    100               //Max receive packet length
#define BT_TX_PKT_SZ    100               //Max transmit packet length

//BTLE services
#define PRIVATE_SERVICE "28238791ec55413086e0002cd96aec9d"
#define PRIVATE_SERVICE_SPI "8ee15902ee6f49dc9cfb5c4c2eff6057"
#define PRIVATE_CHAR_SWITCHES "8f7087bdfdf34b87b10fabbf636b1cd5"
#define PRIVATE_CHAR_POTENTIOMETER "362232e5c5a94af6b30ce208f1a9ae3e"
#define PRIVATE_CHAR_LEDS "cd8306093afa4a9da58b8224cd2ded70"
#define PRIVATE_CHAR_RELAYS "cd83060a3afa4a9da58b8224cd2ded70"
#define PRIVATE_CHAR_ADC_CHAN "cd83060b3afa4a9da58b8224cd2ded70"
#define PRIVATE_CHAR_PIC_SLAVE "cd83060c3afa4a9da58b8224cd2ded70"

//attribute for ISRs that do not alter PSV registers
#define _ISR_NO_AUTO_PSV __attribute__((interrupt,no_auto_psv))

/*******************************************************************************
 * End application configuration settings
 * Hardware settings below
 ******************************************************************************/

// Clock frequency
#define FCY (16000000)                              //8MHz FRC

//RN4020 BTLE
#define BT_OTA_UPD	PORTBbits.RB3
#define BT_OTA_UPD_TRIS	TRISBbits.TRISB3

#define BT_WAKE_HW      LATBbits.LATB10                       //Hardware wake from dormant state; BT_WAKE_HW
#define BT_WAKE_HW_TRIS TRISBbits.TRISB10

#define BT_WAKE_SW      LATBbits.LATB11                       //Deep sleep wake; BT_WAKE_SW
#define BT_WAKE_SW_TRIS TRISBbits.TRISB11

#define BT_CMD      LATAbits.LATA0                 //Place RN4020 module in command mode, low for MLDP mode
#define BT_CMD_TRIS TRISAbits.TRISA0

#define BT_CONNECTED        PORTAbits.RA1                     //RN4020 module is connected to central device
#define BT_CONNECTED_TRIS   TRISAbits.TRISA1

#define BT_WS       PORTAbits.RA2                         //RN4020 module is awake and active
#define BT_WS_TRIS  TRISAbits.TRISA2

#define BT_MLDP_EV      PORTAbits.RA4                         //RN4020 module in MLDP mode has a pending event
#define BT_MLDP_EV_TRIS TRISAbits.TRISA4

//UART
#define U1CTS_TRIS      TRISBbits.TRISB8
#define U1CTS_PORT	PORTBbits.RB8
#define U1CTS_RP_NUM    23

#define U1RTS_TRIS      TRISBbits.TRISB9
#define U1RTS_LAT       LATBbits.LATB9
#define U1RTS_RP_REG    RPOR6bits.RP12R

#define U1RX_TRIS   TRISBbits.TRISB2  //BT_RX
#define U1RX_PORT   PORTBbits.RB2
#define U1RX_RP_NUM 24

#define U1TX_TRIS   TRISBbits.TRISB7  //BT_TX
#define U1TX_LAT    LATBbits.LATB7
#define U1TX_RP_REG RPOR5bits.RP11R

#define UART_RX_IF      IFS0bits.U1RXIF
#define UART_TX_IF      IFS0bits.U1TXIF
#define UART_ER_IF      IFS4bits.U1ERIF

#define UART_TX_IE      IEC0bits.U1TXIE
#define UART_RX_IE      IEC0bits.U1RXIE
#define UART_ER_IE      IEC4bits.U1ERIE
#define UART_TX_EN      U1STAbits.UTXEN
#define UART_EMPTY      U1STAbits.TRMT
#define UART_FULL       U1STAbits.UTXBF

#define UART_TX_BUF     U1TXREG
#define UART_RX_BUF     U1RXREG

#define SPI_X_IF      IFS3bits.SSP2IF
#define SPI_E_IF      IFS3bits.BCL2IF

#define SPI_X_IE      IEC3bits.SSP2IE
#define SPI_E_IE      IEC3bits.BCL2IE

#define SPI_BUF		SSP2BUF
#define SPI_BUF_FULL	SSP2STATbits.BF

// RELAY outputs
#define RELAY1	LATBbits.LATB13 // output 0 (low) turns on relay
#define RELAY2	LATBbits.LATB12
#define RELAY3	LATBbits.LATB4
#define RELAY4	LATBbits.LATB3

// LED outputs
#define LED5 LATBbits.LATB0
#define LED6 LATBbits.LATB0
#define LED7 LATBbits.LATB0

#define SLED LATBbits.LATB14
#define SLED_TRIS TRISBbits.TRISB14

#define LED_TRIS1 TRISBbits.TRISB13
#define LED_TRIS2 TRISBbits.TRISB12
#define LED_TRIS3 TRISBbits.TRISB4
#define LED_TRIS4 TRISBbits.TRISB3

// SPI
#define SPI_CS0_TRIS	TRISAbits.TRISA3
#define SPI_CS1_TRIS	TRISBbits.TRISB15
#define SPI_SDO	TRISBbits.TRISB6
#define SPI_SCK	TRISBbits.TRISB5
#define SPI_SDI	TRISAbits.TRISA7

#define SPI_CS0 LATAbits.LATA3
#define SPI_CS1 LATBbits.LATB15

//Timer initialization
#define TIMER_OFF 0
#define TIMER_ON_PRESCALE1      0x8000
#define TIMER_ON_PRESCALE8      0x8010
#define TIMER_ON_PRESCALE64     0x8020
#define TIMER_ON_PRESCALE256    0x8030

//Timer periods
//32-bit mode with 1:256 postscale below
#define TIMER_5MIN_PERIOD_PS256 ((uint32_t)((FCY / 256) * 300 - 1))
#define TIMER_1MIN_PERIOD_PS256 ((uint32_t)((FCY / 256) * 60 - 1))
#define TIMER_10S_PERIOD_PS256  ((uint32_t)((FCY / 256) * 10 - 1))
#define TIMER_1S_PERIOD_PS256   ((uint16_t)(FCY / 256 - 1))

//16-bit mode with 1:1 postscale below
#define TIMER_1MS_PERIOD        ((uint16_t)(FCY / 1000 - 1))
#define TIMER_100US_PERIOD      ((uint16_t)(FCY / 10000 - 1))
#define TIMER_500US_PERIOD      ((uint16_t)(FCY / 2000 - 1))

#endif //CONFIG_H
