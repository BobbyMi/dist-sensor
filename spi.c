/*
 * spi.c
 *
 *  Created on: 08/mar/2014
 *      Author: massimo
 */




///
/// Registers set for UCB1 SPI interface
/// 4 wires, master mode
///
/*

	P5.5 : UCB1CLK				--->
	P5.4 : UCB1MISO				<---
	P3.7 : UCB1MOSI				--->
	P3.6 : UCB1STE (/CS)  --->

*/


#include <msp430x552x.h>
#include "spi.h"


///
/// the /SS signal must be managed by hand (by programmer)
/// so, it is better to use 3 wire SPI and put convenable /SS signal

/// This function is specific for RTC, that use P2.1 as CE
///
void setUCB1_3Wire_RCT(){

	/// P3.6 : /CS this signal is managed "by hand" not automatically by FMS
	//P3DIR |= BIT6;
	P2DIR |= BIT3 + BIT6;
	CE1_INACTIVE;
	CE2_INACTIVE;

	/// set alternate port function
	P3SEL |= BIT0 + BIT1; 				/// P3.0 (UCB1MOSI) e P3.1 (UCB1MISO)
	P3SEL |= BIT2;						/// P3.2 (UCB1CLK)


	UCB1CTL1 |= UCSWRST;			/// the state machine is in reset mode
	/// msb, ,master, 4 wires, sync, ck inactive low
	//UCB1CTL0 |= UCMSB + UCMST + UCMODE_1 + UCSYNC;

	/// msb, ,master, 3 wires, sync, ck inactive low
	UCB1CTL0 |= UCMSB + UCMST + UCSYNC;
	///
	UCB1CTL1 |= UCSSEL_2; 		/// clock from SMCLK
	/// bit rate: SMCK / 4
	UCB1BR0 = 0x4;						/// :4
	UCB1BR1 = 0;

	/// enable loopback
	//UCB1STAT = UCLISTEN;

	UCB1CTL1 &= ~UCSWRST;			/// initialize the state machine

	/// wait until a tx operation end
	while( UCB1STAT & UCBUSY );
	/// is the same?
	/// while (!(UCB1IFG & UCTXIFG));
}


///
/// transmit a byte
///
void B1tx(unsigned char val){


	/// wait until a tx operation end
	while( UCB1STAT & UCBUSY );
	UCB1TXBUF = val;
	/// wait until a tx operation end
	while( UCB1STAT & UCBUSY );

}


///
/// receive a byte
///
unsigned char B1rx(){

	unsigned char read;
	/// wait until a tx operation end
	while( UCB1STAT & UCBUSY );
	UCB1TXBUF = 0;
	/// wait until a tx operation end
	while( UCB1STAT & UCBUSY );
	/// when write operation is finished, received data is ready.
	read = UCB1RXBUF;
	/// close connection
		return read;
}


