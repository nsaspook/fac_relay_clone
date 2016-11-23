#include <xc.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "app.h"
#include "spi.h"
#include "link.h"

static struct LINK_DATA l_data = {LINK_BYTES};

bool Write_Link_Packet(const uint8_t *data, bool start)
{
	uint16_t i;

	if (!SPI_IsTxData()) {
		for (i = 0; i < LINK_BYTES; i++) { // start with SOF char then data bytes
			if (SPI_GetTXBufferFreeSpace() < 2)
				return false;
			SPI_WriteTxBuffer(*data++); //Load byte into the transmit buffer
		}
		SPI_WriteTxBuffer(0x57); //checkmark for EOF

		if (start) {
			SPI_Speed(1); // high speed
			SPI_CS1 = 0; // select the PIC slave
			SPI_TxStart(); //Start transmitting the bytes
		}
		return true;
	} else
		return false;
}

struct LINK_DATA* Read_Link_Packet(const uint8_t *data)
{
	return memcpy(&l_data, data, LINK_BYTES);
}

struct LINK_DATA* Get_Link_Packet(void)
{
	return &l_data;
}