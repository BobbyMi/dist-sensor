/*
 * spi.h
 *
 *  Created on: 08/mar/2014
 *      Author: massimo
 */

#ifndef SPI_H_
#define SPI_H_



#define CE1_ACTIVE				P2OUT |= BIT3

#define CE2_ACTIVE				P2OUT |= BIT6

													/// P2.3 e P2.6  = 0  :  1011 0111
#define CE1_INACTIVE       		P2OUT &= 0xF7
#define CE2_INACTIVE       		P2OUT &= 0xBF


#endif /* SPI_H_ */
