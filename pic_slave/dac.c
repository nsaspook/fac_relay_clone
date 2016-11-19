
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "config.h"

void DAC_Init(void)
{
	DAC1CONbits.DACEN = 1;
	DAC1CONbits.DACSLP = 1;
	DAC1CONbits.SRDIS = 1;
	DAC1CONbits.DACREF = 2; // Vdd
	AMP1CONbits.AMPEN = 1;
	AMP1CONbits.AMPSLP = 1;
	AMP1CONbits.SPDSEL = 1;
	AMP1CONbits.NINSEL = 5; // voltage follower
	AMP1CONbits.PINSEL = 5; // connect to DAC

	DAC2CONbits.DACEN = 1;
	DAC2CONbits.DACSLP = 1;
	DAC2CONbits.SRDIS = 1;
	DAC2CONbits.DACREF = 2; // Vdd
	AMP2CONbits.AMPEN = 1;
	AMP2CONbits.AMPSLP = 1;
	AMP2CONbits.SPDSEL = 1;
	AMP2CONbits.NINSEL = 5; // voltage follower
	AMP2CONbits.PINSEL = 5; // connect to DAC
}

void SPI_WriteDacBuffer(const uint8_t data, const uint8_t device) // device 2 is DAC2
{
	switch (device) {
	case 2:
		DAC2DAT = data;
		break;
	default:
		DAC1DAT = data;
		break;
	}
}
