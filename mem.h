/*
 * mem.h
 *
 *  Created on: 06/mar/2014
 *      Author: massimo
 */

#ifndef MEM_H_
#define MEM_H_

#define 	NUM_ELEM 			5

#define		NONE				0
#define		NODO				1
#define		CORRIDOIO			2
#define		OSTACOLO			4
#define		VIETATA				8

#define		INF					400


///
/// cella con i dati di distanza e tipo di percorso
typedef struct{
	/// 18 byte; siccome uso 100 celle ho 1800 byte
	/// per lo stack ne sono stati riservati 4096
	int			  	dist[5];
	unsigned char 	attuale;
	unsigned char 	id_cell;
	unsigned char 	tipo;
	unsigned char 	coeffParz;
	char 		  	riga, colonna;
	unsigned char 	direzione;
	unsigned char 	reserved;
} _cellaDist;

///
/// ditanza percorsa dalle ruote
typedef struct{
	int			wDX;
	int			wSX;
} _distRuote;


void copiaC(_cellaDist *src, _cellaDist *dest);
void aggiornaCellaAttiva(_cellaDist *src, _cellaDist *newCell);


#endif /* MEM_H_ */
