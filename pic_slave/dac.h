/* 
 * File:   dac.h
 * Author: root
 *
 * Created on November 17, 2016, 11:34 AM
 */

#ifndef DAC_H
#define	DAC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

	void DAC_Init(void);
	void UART_WriteDacBuffer(const uint8_t, const uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* DAC_H */

