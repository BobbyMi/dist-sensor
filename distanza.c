/*
 * distanza.c
 *
 *  Created on: 25/feb/2014
 *      Author: massimo
 */

extern float inv_m[], soglia[];
/// routine che calcolano la distanza letta dai sensori

int distanza(int valMedi[], float dist[], int numElem){
/// dal grafico si ha la seguente spezzata
/// V - V0 = (V1 - V0)/(F1 - F0) * (F - F0) =>
/// (V - V0) * (F1 - F0)/(V1 - V0) + F0 = F
/// ((V - V0) * (F1 - F0) + F0(V1 - V0))/(V1 - V0) = F
/// x = 1/F = (V1 -V0)/((V - V0)*(F1 - F0) + F0 * (V1 - V0))
	int i;

	for (i = 0; i < numElem; i++){
		if (valMedi[i] < soglia[0]){
			dist[i] = 40.0;
			continue;
		}
		if (valMedi[i] < soglia[1]){
			dist[i] = 1/((valMedi[i] - soglia[0])*inv_m[i] +soglia[0]);
			continue;
		}

		if (valMedi[i] < soglia[2]){
			dist[i] = 1/((valMedi[i] - soglia[1])*inv_m[i] + soglia[1]);
			continue;
		}

		if (valMedi[i] < soglia[3]){
			dist[i] = 1/((valMedi[i] - soglia[2])*inv_m[i] + soglia[2]);
			continue;
		}
		if (valMedi[i] < soglia[4]){
			dist[i] = 1/((valMedi[i] - soglia[3])*inv_m[i] + soglia[3]);
			continue;
		}
		if (valMedi[i] < soglia[5]){
			dist[i] = 1/((valMedi[i] - soglia[4])*inv_m[i] + soglia[4]);
			continue;
		}
		if (valMedi[i] < soglia[6]){
			dist[i] = 1/((valMedi[i] - soglia[5])*inv_m[i] + soglia[5]);
			continue;
		}
		if (valMedi[i] < soglia[7]){
			dist[i] = 1/((valMedi[i] - soglia[6])*inv_m[i] + soglia[6]);
			continue;
		}

		if (valMedi[i] < soglia[8]){
			dist[i] = 1/((valMedi[i] - soglia[7])*inv_m[i] + soglia[7]);
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
