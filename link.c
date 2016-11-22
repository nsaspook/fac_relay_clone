#include <xc.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "app.h"
#include "spi.h"
#include "link.h"

struct LINK_DATA l_data = {0x19};

bool Write_Link_Packet(const uint8_t *data, uint16_t count)
{
	uint16_t i;

	if (!SPI_IsTxData()) {
		for (i = 0; i < count; i++) { // start with SOF char then data bytes
			if (SPI_GetTXBufferFreeSpace() < 2)
				return false;
			SPI_WriteTxBuffer(*data++); //Load byte into the transmit buffer
		}
		SPI_WriteTxBuffer(0x57); //checkmark for EOF
		SPI_CS1 = 0; // select the PIC slave
		SPI_Speed(1); // high speed
		SPI_TxStart(); //Start transmitting the bytes

		return true;
	} else
		return false;
}

struct LINK_DATA* Read_Link_Packet(const uint8_t *data)
{
	return memcpy(&l_data, data, LINK_BYTES);
}