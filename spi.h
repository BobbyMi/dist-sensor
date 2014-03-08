/*
 * spi.h
 *
 *  Created on: 08/mar/2014
 *      Author: massimo
 */

#ifndef SPI_H_
#define SPI_H_


																	///1011 1111
#define SS_ACTIVE				P3OUT &= 0xBF
																	///0100 0000
#define SS_INACTIVE				P3OUT |= 0x40

													/// P2.1 = 1  :  0000 0010
#define CE_ACTIVE				P2OUT |= 0x2

													/// P2.1 = 0  :  1111 1101
#define CE_INACTIVE       		P2OUT &= 0xFD


#endif /* SPI_H_ */
