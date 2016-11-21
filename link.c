#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "config.h"
#include "app.h"
#include "spi.h"
#include "link.h"

struct LINK_DATA	l_data;

bool Write_Link_Packet(const uint8_t *data, uint16_t count)
{
	uint16_t i;

	if (!SPI_IsTxData()) {
		for (i = 0; i < count; i++) {
			SPI_WriteTxBuffer(*data++); //Load byte into the transmit buffer
		}
		SPI_WriteTxBuffer(0x57); //checkmark
		SPI_CS1 = 0; // select the PIC slave
		SPI_Speed(1); // high speed
		SPI_TxStart(); //Start transmitting the bytes

		return true;
	} else
		return false;
}