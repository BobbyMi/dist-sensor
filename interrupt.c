/*
 * interrupt.c
 *
 *  Created on: 23/feb/2014
 *      Author: massimo
 */

#include <msp430.h>
#include "init.h"

//INTERRUPT
extern volatile int adcResults[], flag;

#pragma vector = ADC12_VECTOR
__interrupt void ADC12ISR (void){


	switch(__even_in_range(ADC12IV,34)){
		case  0: break;                           	// Vector  0:  No interrupt
		case  2: break;                           	// Vector  2:  ADC overflow
		case  4: break;                          	// Vector  4:  ADC timing overflow
		case  6: break;                           	// Vector  6:  ADC12IFG0
		case  8: break;								// Vector  8:  ADC12IFG1
		case 10: break;                           	// Vector 10:  ADC12IFG2
		case 12: break;                           	// Vector 12:  ADC12IFG3
		case 14: break;                           	// Vector 14:  ADC12IFG4
		case 16:									// Vector 16:  ADC12IFG5

			adcResults[0] = ADC12MEM0;
			adcResults[1] = ADC12MEM1;
			adcResults[2] = ADC12MEM2;
			adcResults[3] = ADC12MEM3;
			adcResults[4] = ADC12MEM4;
			adcResults[5] = ADC12MEM5;
			/// segnala la necessita' di aggiornare la media
			flag = 1;
		break;
		case 18: break;                           // Vector 18:  ADC12IFG6
		case 20: break;                           // Vector 20:  ADC12IFG7
		case 22: break;                           // Vector 22:  ADC12IFG8
		case 24: break;                           // Vector 24:  ADC12IFG9
		case 26: break;                           // Vector 26:  ADC12IFG10
		case 28: break;                           // Vector 28:  ADC12IFG11
		case 30: break;                           // Vector 30:  ADC12IFG12
		case 32: break;                           // Vector 32:  ADC12IFG13
		case 34: break;                           // Vector 34:  ADC12IFG14
		default: break;
	 }
}



volatile unsigned int contatore = 0;

// Timer1 A0 interrupt service routine
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{

	//P1OUT ^= 1;
	contatore++;
	if ((contatore & 7) == 0)
		/// blink led verde
		P4OUT ^= BIT7;

}

///
/// Riceve ad interruzione un carattere via seriale
///

extern volatile unsigned char RXBuffer[];
extern volatile unsigned char RX_PTR;

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA1IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    RXBuffer[RX_PTR] = UCA1RXBUF;
    UCA1TXBUF = RXBuffer[RX_PTR++];         // TX -> RXed character
    RX_PTR &= DIM_RX_BUFF - 1;
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}

