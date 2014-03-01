/*
 *    definisce le funzioni che caratterizzano il giroscopio
 *
 */


#include "init.h"

const char num_sens = 6;


volatile int matrix0[7][10]; //matrice moto rettilineo
volatile int matrix1[7][10]; //matrice rotazione oraria (riga aggiuntiva per contenere info dal giroscopio)
volatile int matrix2[7][10]; //matrice rotazione antioraria

volatile char pos0 = 0;
volatile char pos1 = 0;
volatile char pos2 = 0;

volatile char matrix0_ready = off;
volatile char matrix1_ready = off;
volatile char matrix2_ready = off;

//	matrice per contenere i dati delle conversioni durante moti rettilinei
// -la colonna indica il n� della conversione
// -la riga individua i dati provenienti da un dato sensore
//
//		0	1	2	3	4	5	6	7	8	9
//  A0	x	x 	x	x	x	x	x	x	x	x	fronte
//	A1	x	x	x	x	x	x	x	x	x	x
//============================================
//	A2	x	x	x	x	x	x	x	x	x	x	lato
//	A3	x	x	x	x	x	x	x	x	x	x
//============================================
//	A4	x	x	x	x	x	x	x	x	x	x	lato
//	A5	x	x	x	x	x	x	x	x	x	x
//	
//
// matrice 2 e 3: quando il giroscopio e' attivo salva le conversioni qui
// -l'ultima riga rappresenta il giroscopio. 
//ovviamente sara'� necessaria una funzione apposita per il giroscopio stesso
//
//		0	1	2	3	4	5	6	7	8	9
//  A0	x	x 	x	x	x	x	x	x	x	x	fronte
//	A1	x	x	x	x	x	x	x	x	x	x
//============================================
//	A2	x	x	x	x	x	x	x	x	x	x	lato
//	A3	x	x	x	x	x	x	x	x	x	x
//============================================
//	A4	x	x	x	x	x	x	x	x	x	x	lato
//	A5	x	x	x	x	x	x	x	x	x	x
//============================================
//	Gyr x	x	x	x	x	x	x	x	x	x	giroscopio 0= moto rettilineo
//														   1= rotazione oraria
//														   2= rotazione antioraria




void data_function( int sensori[], int giroscopio[] ){

char c,j,i;// variabili per iterazioni





switch (giroscopio[c]){
	//no rotazione
	case 0:
	//controllo che la matrice non sia pronta, se è pronta deve essere ancora elaborata
	if(matrix0_ready == off){		

		//controllo se la matrice1 è piena, se è così 
		//avverto che è pronta per essere elaborata
		if(pos0==10){
		pos0=0;
		matrix0_ready = on;
		}
		//inserisco i dati nella matrice, l'ultima riga è di soli zeri poichè il giroscopio non ci interessa
		for(i=0;i< num_sens;i++){		
		matrix1[i][pos0]= sensori[i];
		matrix1[num_sens][pos0] = 0;
		}
		pos0++;

		pos1 = 0;	//se durante le varie conversioni il giroscopio si è attivato per un periodo 
		pos2 = 0;	// inferiore a quello necessario per riempire la matrice di rotazione, allora la stessa
					//verrà risovrascritta senza essere elaborata
	}
	else
	break;
	
	//IN ALTERNATIVA AI 3 VALORI DEL GIROSCOPIO (0,1 e 2) SI PUÒ VALUTARE L'UTILIZZO DEI VALORI DATI DAL GIROSCOPIO
	//ESPRESSI IN gradi o radianti (CON SEGNO). LO SWITCH SI RIDURREBBE A DUE SOLI CASI; CIOÈ DEL CASE 0 E DEL CASE DI 
	//DEFAULT:
	//
	// default:
	// if(giroscopio[] > 0) //rotazione oraria
	// 		if(matrix1_ready == off){
	//		...
	//		...
	//
	// if(giroscopio[] < 0) //rotazione antioraria
	// 		if(matrix2_ready == off){
	//		...
	//		...
	// break;


	//rotazione oraria 
	case 1:
	
			if(matrix1_ready == off){
				if(pos1==10){
				pos1=0;
				matrix1_ready = on;
				}
				
				for(j=0;j< num_sens;j++){		
				matrix1[j][pos1]= sensori[j];
				matrix1[num_sens][pos1]= giroscopio[pos1];
				}
				pos1++;
	
			}
	
	break;

	//rotazione antioraria
	case 2:
	
			if(matrix2_ready == off){
				if(pos2==10){
				pos2=0;
				matrix2_ready = on;
				}
				
				for(j=0;j< num_sens;j++){		
				matrix2[j][pos2]= sensori[j];
				matrix2[num_sens][pos2]= giroscopio[pos2];
				}
				pos2++;
	
			}
	
	break;




	default:
	break;

}

}







