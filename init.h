/*
 * init.h
 *
 *  Created on: 23/feb/2014
 *      Author: massimo
 */

#ifndef INIT_H_
#define INIT_H_

#include <stdio.h>
#include <stdlib.h>


float* adc_function(char a, char b, char c, char d, char e, char f);

unsigned long int setDCO(unsigned long int mhz);
void initPort1(void);

void initUART1(unsigned long bitRate, unsigned long fdco);
void initADC(unsigned char channel);
void initADCmultiCH(unsigned char channel, unsigned char beg, unsigned char end);
void initTIMER(unsigned long FDCO);
double leggiTemepratura();
void double2string(double a, char* b);

void initMCU(void);
void setupCoeff(float coeff);

void initI2C_B1(unsigned long int fdco, unsigned long int speed, unsigned char devAddr);
unsigned char readI2CByteFromAddress(unsigned char reg_address, char *status);
char writeI2CByte(unsigned char data, unsigned char reg_address);
char readI2C_N_Byte( unsigned char reg_address, unsigned char numElm, unsigned char buff[] );

int fputc(int _c, register FILE *_fp);
int fputs(const char *_ptr, register FILE *_fp);


///////////////////////////////////////////////
#define		NACK_ERR		1
#define		OK				0
#define		BUS_BUSY		2
#define		NOT_PRESENT		3
#define		OFF				4

#define 		on  		1
#define	 		off 		0

#define 	DIM_RX_BUFF		32



//////////////////////////////////////////////
///
/// CLOCK FREQUENCY
///
//////////////////////////////////////////////
/* MHz */
#define		FDCO	22118400
#define		FDCO1	24576000

#endif /* INIT_H_ */
