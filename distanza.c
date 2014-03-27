/*
 * distanza.c
 *
 *  Created on: 25/feb/2014
 *      Author: massimo
 */

#include "init.h"
#include "mem.h"

extern float inv_m[], soglia[];
/// routine che calcolano la distanza letta dai sensori



int distanza(int valMedi[], int distS[], int numElem){
/// dal grafico si ha la seguente spezzata
/// V - V0 = (V1 - V0)/(F1 - F0) * (F - F0) =>
/// (V - V0) * (F1 - F0)/(V1 - V0) + F0 = F
/// ((V - V0) * (F1 - F0) + F0(V1 - V0))/(V1 - V0) = F
/// x = 1/F = (V1 -V0)/((V - V0)*(F1 - F0) + F0 * (V1 - V0))
	int i, distanzaR;
	float f, f1;
	for (i = 0; i < numElem; i++){
		if (valMedi[i] < soglia[0]){
			distS[i] = 400;
			continue;
		}
		if (valMedi[i] < soglia[1]){
			f = 1/((valMedi[i] - soglia[0])*inv_m[i] +soglia[0]);
			reduceToChar(f, distS, i);
			continue;
		}

		if (valMedi[i] < soglia[2]){
			f = 1/((valMedi[i] - soglia[1])*inv_m[i] + soglia[1]);
			reduceToChar(f, distS, i);
			continue;
		}

		if (valMedi[i] < soglia[3]){
			f = 1/((valMedi[i] - soglia[2])*inv_m[i] + soglia[2]);
			reduceToChar(f, distS, i);
			continue;
		}
		if (valMedi[i] < soglia[4]){
			f = 1/((valMedi[i] - soglia[3])*inv_m[i] + soglia[3]);
			reduceToChar(f, distS, i);
			continue;
		}
		if (valMedi[i] < soglia[5]){
			f = 1/((valMedi[i] - soglia[4])*inv_m[i] + soglia[4]);
			reduceToChar(f, distS, i);
			continue;
		}
		if (valMedi[i] < soglia[6]){
			f = 1/((valMedi[i] - soglia[5])*inv_m[i] + soglia[5]);
			reduceToChar(f, distS, i);
			continue;
		}
		if (valMedi[i] < soglia[7]){
			f = 1/((valMedi[i] - soglia[6])*inv_m[i] + soglia[6]);
			reduceToChar(f, distS, i);
			continue;
		}

		if (valMedi[i] < soglia[8]){
			f = 1/((valMedi[i] - soglia[7])*inv_m[i] + soglia[7]);
			reduceToChar(f, distS, i);
			continue;
		}

	}
	return 0;
}

///
/// imposta i coefficienti della pendenza
void setupCoeff(float coeff){
	int i;
	for (i = 0; i < 8; i++)
		inv_m[i] *= coeff;
}

///
/// trasforma un float in char
///
void reduceToChar(float f, int distS[], int indice){
	int distanzaR;
	float f1;

	f1 = round(f);
	distanzaR = (int) f1;
	distS[indice] = distanzaR & 255;
}

///
/// copia della cella
///
void copiaC(_cellaDist *src, _cellaDist *dest ){
	int i = 0;
	for (i = 0; i < NUM_ELEM; i++)
		dest->dist[i] = src->dist[i];
	dest->attuale = src->attuale;
	dest->coeffParz = src->coeffParz;
	dest->id_cell = src->id_cell;
	dest->tipo = src->tipo;
	dest->reserved = src->reserved;
	dest->riga = src->riga;
	dest->colonna = src->colonna;
	dest->direzione = src->direzione;

}

///
/// aggiorna lo stato della cella attiva
void aggiornaCellaAttiva(_cellaDist *src, _cellaDist *newCell){

}

///
///
void aggiornaCellaMobile(){


}

///
/// interpreta se la cella attuale e' gia' mappata nel labirinto
void interpretaCella( _cellaDist vCell[], _cellaDist * cAttPtr ){

	int i;
	/// scorre fino alla prima cella libera
	while (vCell[i++].tipo != NONE);
	/// e confronta la cella con quella attuale dove c'è l'ultima misura
	if (cAttPtr->dist[0] < INF){
	/// la distanza misurata e' minore del massimo misurabile dal sensore

	}
	vCell[0].tipo = CORRIDOIO;

}
