
/*
 * funzioni di gestione ed inizializzazione del convertitore ADC
 * 																	*/



#include<msp430.h>


volatile  int  flag = 0;


///
/// calcola la media di N grandezze campionate M volte
///

int media(int* vettore, int* average, int n, int M){

	const int deltaD = 100;
	int i;

	/// intanto valuta se deve calcolare la media
	if (flag){
		flag = 0;
		for (i = 0; i < n; i++){
			average[i] += vettore[i];
			average[i] >>= 1;
		}

		return 0;
	}
	return -1;
}
				//a = A0, b = A1,..., f = A5
/*
unsigned int* adc_function(char a, char b, char c, char d, char e, char f){

	//dichiaro le variabili che utilizzera' per il controllo dei buffer dei dati.
	//Una volta che il buffer sara'  al completo lo fara' sovrascrivere
	char index = 0;

	char flag = 0;


	for(i = 0; i<65000; i++);	//faccio perdere tempo al micro in modo da dare tempo all'adc per convertire.

	//mando i risultati in uscita se il ciclo di conversione Ã¨ terminato
	while(flag == 0){}

	return result;
}
*/


/// ADC init with INTeRnAL REFERENCE
void initADCmultiCH(unsigned char channel, unsigned char beg, unsigned char end){

	/// init port P6.0 ... P6.5
	P6SEL |= BIT0 + BIT1 + BIT2 + BIT3 + BIT4+ BIT5;
	/// set reference register for internal reference: enable, 2.5V
	REFCTL0 = REFMSTR + REFVSEL_2 + REFON;
	/// disable the AD unit
	ADC12CTL0 = 0;
	/// set the AD to have internal ck, not divided, with sequence of channel operation
	/// sequence start at ADC12MEM0 memory cell.
	ADC12CTL1 =  ADC12SHP + ADC12CONSEQ_1;
	//ADC12CTL1 =  ADC12SHP;

	/// 12 bit conversion
	ADC12CTL2 = ADC12RES_2;

	/// time of conversion: 6us * 6 channels + 6 * 13 clk cycles (1 clk = 0,2us) = 36 + 6 * 26 = 36 + 156 = 192 us
	ADC12CTL0 |= ADC12SHT0_3 + ADC12ON;			/// sample time = 32 clk cycles. At 5MHz => 0.2u * 32 = 6us
	ADC12CTL0 |= ADC12MSC;						/// enable multiple conversion

	/// set the last channel in the sequence
	ADC12MCTL0 = ADC12SREF_1 + ADC12INCH_0;
	ADC12MCTL1 = ADC12SREF_1 + ADC12INCH_1;
	ADC12MCTL2 = ADC12SREF_1 + ADC12INCH_1;
	ADC12MCTL3 = ADC12SREF_1 + ADC12INCH_1;
	ADC12MCTL4 = ADC12SREF_1 + ADC12INCH_1;

	/// set the last channel in the sequence
	ADC12MCTL5 = ADC12SREF_1 + ADC12INCH_1 	+ ADC12EOS;

	__delay_cycles(300);                      	// 35us delay to allow Ref to settle
		                                        // based on default DCO frequency.

	/// Enable of conversion
	//ADC12CTL0 |= ADC12ENC;

	ADC12IE = ADC12IE5;                           // Enable ADC12IFG.5
	///while (ADC12CTL1 & ADC12BUSY);
	///lettura = ADC12MEM0;

}

