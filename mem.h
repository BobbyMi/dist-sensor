/*
 * mem.h
 *
 *  Created on: 06/mar/2014
 *      Author: massimo
 */

#ifndef MEM_H_
#define MEM_H_

#define NUM_ELEM 			5

#define	NODO				1
#define	CORRIDOIO			2
#define	OSTACOLO			4
#define	VIETATA				8


///
/// cella con i dati di distanza e tipo di percorso
typedef struct{

	unsigned char dist[5];
	unsigned char attuale;
	unsigned char id_cell;
	unsigned char tipo;
	unsigned char coeffParz;
	unsigned char riga, colonna;
	unsigned char direzione;
	unsigned char reserved;


} _cellaDist;

///
/// ditanza percorsa dalle ruote
typedef struct{
	unsigned char wDX;
	unsigned char wSX;
} _distRuote;


void copiaC(_cellaDist *src, _cellaDist *dest);
void aggiornaCellaAttiva(_cellaDist *src, _cellaDist *newCell);


#endif /* MEM_H_ */
