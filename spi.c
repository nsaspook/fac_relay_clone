/* SPI Master Driver */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "spi.h"
#include "config.h"

//SPI receive buffer type

typedef struct {
	volatile uint8_t buffer[SIZE_SPI_Buffer];
	volatile uint8_t volatile *head;
	volatile uint8_t *tail;
	volatile uint16_t byteCount;
} SPI_RX_BUFFER_T;

//SPI transmit buffer type

typedef struct {
	volatile uint8_t buffer[SIZE_SPI_Buffer];
	volatile uint8_t *head;
	volatile uint8_t volatile *tail;
	volatile uint16_t byteCount;
} SPI_TX_BUFFER_T;

//Buffer instances
static SPI_RX_BUFFER_T rxBuf;
static SPI_TX_BUFFER_T txBuf;

void SPI_Init(void)
{
	SPI_SDO = 0;
	SPI_SCK = 0;
	SPI_SDI = 1;
	SPI_CS0 = 1;
	rxBuf.tail = &rxBuf.buffer[0]; //Initialize the pointers
	rxBuf.head = &rxBuf.buffer[0];
	txBuf.tail = &txBuf.buffer[0];
	txBuf.head = &txBuf.buffer[0];
	txBuf.byteCount = 0;
	rxBuf.byteCount = 0;

	/* SPI2 HW setup */
	SSP2CON1bits.SSPM = 2; // SPI SCK speed
	SSP2CON1bits.CKP = 0; // SCK polarity mode 0,0
	SSP2STATbits.CKE = 0; // SCK select 
	SSP2STATbits.SMP = 0; // sample mid
	SSP2CON1bits.SSPEN = 1; // enable spi ports
	PADCFG1bits.SCK2DIS = 0;
	PADCFG1bits.SDA2DIS = 0;

	SPI_X_IF = 0; //Clear SPI interrupt flags
	SPI_E_IF = 0;
	SPI_X_IE = 0; //Setup SPI Receive and Error interrupt
	SPI_E_IE = 1;
}

void SPI_ClearBufs(void)
{
	__builtin_disi(0x3FFF); //disable interrupts
	rxBuf.tail = &rxBuf.buffer[0]; //Initialize the pointers
	rxBuf.head = &rxBuf.buffer[0];
	txBuf.tail = &txBuf.buffer[0];
	txBuf.head = &txBuf.buffer[0];
	txBuf.byteCount = 0;
	rxBuf.byteCount = 0;
	__builtin_disi(0); //enable interrupts
}

void SPI_TxStart(void)
{
	__builtin_disi(0x3FFF); //disable interrupts
	if (txBuf.byteCount) { // prime the transmit interrupt
		/* write data here */
		SPI_X_IF = 0; //Clear interrupt flag
		SPI_BUF = *txBuf.tail++; //Load next byte into the TX buffer
		if (txBuf.tail > &txBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if end of buffer
			txBuf.tail = &txBuf.buffer[0]; //Wrap pointer to beginning
		}
		txBuf.byteCount--; //Decrement byte count
		SPI_X_IE = 1; //Enable transmit interrupts
		__builtin_disi(0); //enable interrupts
		return;
	}
	__builtin_disi(0); //enable interrupts
	return;
}

bool SPI_IsNewRxData(void)
{
	__builtin_disi(0x3FFF); //disable interrupts
	if (rxBuf.byteCount == 0) { //Check if data in buffer
		__builtin_disi(0); //enable interrupts
		return(false); //No bytes in the buffer so return false
	}
	__builtin_disi(0); //enable interrupts
	return(true); //There are bytes in the buffer
}

uint8_t SPI_ReadRxBuffer(void)
{
	uint8_t Temp;

	__builtin_disi(0x3FFF); //disable interrupts
	if (rxBuf.byteCount == 0) { //For safety, do not allow read of empty buffer
		__builtin_disi(0); //enable interrupts
		return(0); //Return zero if there is nothing in the buffer
	}

	rxBuf.byteCount--; //Decrement byte count
	__builtin_disi(0); //enable interrupts
	Temp = *rxBuf.tail++; //Get the byte and increment the pointer
	if (rxBuf.tail > &rxBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if at end of buffer
		rxBuf.tail = &rxBuf.buffer[0]; //then wrap the pointer to beginning
	}
	return(Temp);
}

bool SPI_IsTxData(void)
{
	__builtin_disi(0x3FFF); //disable interrupts
	if (txBuf.byteCount == 0) { //Check if data in buffer
		__builtin_disi(0); //enable interrupts
		return(false); //No bytes in the buffer so return false
	}
	__builtin_disi(0); //enable interrupts
	return(true); //There are bytes in the buffer
}

void SPI_WriteTxBuffer(const uint8_t TxByte)
{
	*txBuf.head++ = TxByte; //Put the byte in the transmit buffer and increment the pointer
	if (txBuf.head > &txBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if at end of buffer
		txBuf.head = &txBuf.buffer[0]; //Wrap pointer to beginning
	}
	__builtin_disi(0x3FFF); //disable interrupts
	if (txBuf.byteCount < SIZE_SPI_Buffer) { //Increment byte count
		txBuf.byteCount++;
	}
	__builtin_disi(0); //enable interrupts
}

//**********************************************************************************************************************
// Return the number of bytes free in the TX buffer

uint16_t SPI_GetTXBufferFreeSpace(void)
{
	uint16_t space;

	__builtin_disi(0x3FFF); //disable interrupts            
	space = SIZE_SPI_Buffer - txBuf.byteCount;
	__builtin_disi(0); //enable interrupts
	return space;
}

//Peek at buffer tail

uint8_t SPI_PeekRxBuffer(void)
{
	__builtin_disi(0x3FFF); //disable interrupts
	if (rxBuf.byteCount == 0) { //Check if pointers are the same
		__builtin_disi(0); //enable interrupts
		return(NULL); //No bytes in the buffer so return NULL
	} else {
		__builtin_disi(0); //enable interrupts
		return *rxBuf.tail;
	}
}

void __attribute__((interrupt, no_auto_psv)) _MSSP2Interrupt(void)
{
	SPI_X_IF = 0; //Clear interrupt flag
	if (txBuf.byteCount > 0) { //Check if more data is in the buffer
		/* read data HERE */
		*rxBuf.head++ = SPI_BUF; //Put received byte in the buffer
		if (rxBuf.head > &rxBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if end of buffer
			rxBuf.head = &rxBuf.buffer[0]; //Wrap pointer to beginning
		}
		if (rxBuf.byteCount < SIZE_SPI_Buffer) { //Increment byte count
			rxBuf.byteCount++;
		}

		/* write data here */
		SPI_BUF = *txBuf.tail++; //Load next byte into the TX buffer
		if (txBuf.tail > &txBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if end of buffer
			txBuf.tail = &txBuf.buffer[0]; //Wrap pointer to beginning
		}
		txBuf.byteCount--; //Decrement byte count
	} else {
		/* read data HERE */
		*rxBuf.head++ = SPI_BUF; //Put received byte in the buffer
		if (rxBuf.head > &rxBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if end of buffer
			rxBuf.head = &rxBuf.buffer[0]; //Wrap pointer to beginning
		}
		if (rxBuf.byteCount < SIZE_SPI_Buffer) { //Increment byte count
			rxBuf.byteCount++;
		}
		SPI_X_IE = 0; //No more data to transmit, so stop interrupts
		SPI_CS0 = 1; // deselect all devices here
//		SPI_CS1 = 1;
	}
}

void __attribute__((interrupt, no_auto_psv)) _MSSP2BCInterrupt(void)
{
	SPI_E_IF = 0; //Clear interrupt flag

	//Handle an overflow error by reading next byte and clearing flags
	if (SSP2CON1bits.WCOL || SSP2CON1bits.SSPOV) {
		*rxBuf.head++ = SPI_BUF; //Put received byte in the buffer
		if (rxBuf.head > &rxBuf.buffer[SIZE_SPI_Buffer - 1]) { //Check if end of buffer
			rxBuf.head = &rxBuf.buffer[0]; //Wrap pointer to beginning
		}
		if (rxBuf.byteCount < SIZE_SPI_Buffer) { //Increment byte count
			rxBuf.byteCount++;
		}
		SSP2CON1bits.WCOL = 0;
		SSP2CON1bits.SSPOV = 0;
	}

	//Clear any other error bits

}
