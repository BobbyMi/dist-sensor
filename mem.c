/*
 * mem.c
 *
 *  Created on: 23/feb/2014
 *      Author: massimo
 */

///
/// qui dichiaro i buffer di memoria
///
volatile unsigned char RXBuffer[32];
int adcResults[24], mediaCampioni[6];

/// costanti modificabili
volatile float inv_m[8] =
{		0.06777,
		0.07337,
		0.07653,
		0.07919,
		0.08725,
		0.1067,
		0.7459,
		0.0
};

///
/// soglie di tensione tramite le quali applicare
/// i coefficienti nelle costanti modificabili
///
volatile float soglia[8] =
{ 		0.247,
		0.336,
		0.432,
		1.024,
		1.416,
		1.872,
		2.4,
		2.44,
};


/// puntatori
volatile unsigned char RX_PTR = 0, RX_read_PTR = 0;

