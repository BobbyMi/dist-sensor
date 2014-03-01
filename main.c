

/*
 * main.c
 */
#include <msp430x552x.h>
#include <stdio.h>
#include <string.h>
#include "init.h"
#include "gyro_init.h"
#include "accel_init.h"
#include "compass_init.h"

extern volatile unsigned int contatore;

/*
 * main.c
 */
void main(void) {
	volatile unsigned int i;
	volatile unsigned char valore;
	double temperatura;
	char conv[30], stato;
	unsigned char buff[8] = {0,0,0,0,0,0,0,0};
	int x, y ,z;
	gyro G;



	// Stop watchdog timer
    WDTCTL = WDTPW | WDTHOLD;

    /// set Internal DCO. This value is 2^15*3^2*5^2*3, so it is a mutiple of 2^9*3^2*5^2 = 115200
    setDCO(FDCO);

    /// initialize UART1
    initUART1(38400, FDCO);

    initMCU();
    /// init port 1
    initPort1();
    P1REN = 2;			/// 0 0 0 0 0 0 1 0  pull up
    P1OUT = 2;

    P4DIR = 0x80;
    P4OUT = 0x80;

    initADCmultiCH(6, 0, 5);
    initTIMER(FDCO);

	// Enable interrupt
	 __bis_SR_register(GIE);

	/// wait until P1.1 isn't pressed
	while(P1IN & BIT1);

	/*					INIT GYRO REGISTER			*/
	G.IsOn = OFF;
	 /// initialize I2C gyroscope module
	initI2C_B1(FDCO, 800000, GYRO_ADDR);

	 //valore = readI2CByteFromAddress(WHO_AM_I, &stato);
	if (readI2CByteFromAddress(WHO_AM_I, &stato) == 0xD4)
		G.IsPresent = OK;
	else
		G.IsPresent = NOT_PRESENT;
	valore = readI2CByteFromAddress(CTRL_REG1, &stato);
	/// scrivo nel registro 0x20 il valore 0x0F, cioe' banda minima, modulo on e assi on
	stato =  writeI2CByte(CTRL_REG1, 0x0F);
	if(readI2CByteFromAddress(CTRL_REG1, &stato) == 0x0F)
		G.IsOn = OK;
	/// set FS to 500 degree per sec.
	stato =  writeI2CByte(CTRL_REG4, FS_500);
	valore = readI2CByteFromAddress(CTRL_REG4, &stato);
	/// set FIFO mode and water mark
	//stato = writeI2CByte(FIFO_CTRL_REG, FIFO_MODE + 20);
	//valore = readI2CByteFromAddress(FIFO_CTRL_REG, &stato);
	/// enable FIFO
	//stato =  writeI2CByte(CTRL_REG5, FIFO_EN);
	/// enable interrupt when samples number in greater than WTM
	//stato = writeI2CByte(CTRL_REG3, I2_WTM);

	/*														*/

	/*          INIT ACCELEROMETER REGISTERS                */
	//initI2C_B1(FDCO, 800000, ACCEL_ADDR);
	//valore = readI2CByteFromAddress(CTRL_REG1_A, &stato);
	//stato =  writeI2CByte(CTRL_REG1_A, ODR1 + ODR0 + ZaxEN + YaxEN + XaxEN);
	/*														*/

	/*       	   INIT COMPASS REGISTERS
	initI2C_B1(FDCO, 800000, COMPASS_ADDR);
	valore = readI2CByteFromAddress(CRA_REG_M, &stato);
	stato = readI2C_N_Byte(CRA_REG_M, 3, buff);
	stato =  writeI2CByte(MR_REG_M, 0);
	valore = readI2CByteFromAddress(MR_REG_M, &stato);*/

	i = 0;
    while(1){
    	i++;
    	//temperatura = leggiTemepratura();
 //   	double2string(temperatura, conv);
    	//printf("temperatura %f\r\n", temperatura);
    	P4OUT ^= 0x80;
    	//valore = readI2CByteFromAddress(STATUS_REG_M, &stato);	/// compass
    	valore = readI2CByteFromAddress(STATUS_REG, &stato);
    	if (valore != 0){
    	/// legge i dati da tutti i registri del giroscopio
    		//stato = readI2C_N_Byte(OUT_X_L_M, 6, buff);			/// compass
    		stato = readI2C_N_Byte(OUT_X_L, 6, buff);
    		//valore = readI2CByteFromAddress(STATUS_REG, &stato);
    		x = (int)((buff[1]<< 8) + buff[0]);
    		z = (int)((buff[3]<< 8) + buff[2]);
    		y = (int)((buff[5]<< 8) + buff[4]);
    		printf("asse x: %d\t",x);
    		printf("\tasse y: %d\t",y);
    		printf("\tasse z: %d\r\n",z);
    		//printf("contatore: %d\r\n", contatore);
    		i = 0;
    		contatore = 0;
    		P1OUT ^= 1;
    	}
    }
}





