
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
//#include <iostream>
#include <stdio.h>
#include <string.h>
#include <SI_EFM8BB3_Register_Enums.h>                // SFR declarations
#include <signal.h>
#include <stdio.h>
#include "bsp.h"
//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
//
// Note: the software watchdog timer is not disabled by default in this
// example, so a long-running program will reset periodically unless
// the timer is disabled or your program periodically writes to it.
//
// Review the "Watchdog Timer" section under the part family's datasheet
// for details. To find the datasheet, select your part in the
// Simplicity Launcher and click on "Data Sheet".
//
//----------------------------------------------------------------------------- 
int z;
int OP1 ;
int OP2 ;
int D1 ;
int D2 ;
int D3 ;
int D4 ;
int y;

#define OP_CODE_COMMANDS 3
static uint16_t frequency[OP_CODE_COMMANDS] = {
		3,
		0,
		0
};

static uint8_t OP_CODES = 1;

#define DATA_OUTPUTS 3
static uint16_t frequencies[DATA_OUTPUTS] = {
		0,
		7,
		3

};

int y = frequency;
int x = frequencies;

static uint8_t DATA = 1;


int main (void)
{
	//char x[10]; //char strings x and y I was gonna use to store the data inputted by the user. X should be the operation, Y is the value being inputted. You need to figure out how to actually get that to be read by the rest of the program because I was not sure.
	//char y[10];
	
//	std::cout << "Please choose an operation and number./n and the press enter";
	//fgets ( , 10, stdin );
	
	if (x = 0) { // respective opcodes are produced based on x
		OP1 = 1;
		OP2 = 0	;
	}else if (x = 1) {
		OP1 = 0 ;
		OP2 = 1	 ;
	}else if (x = 2) {
		OP1 = 0 ;
		OP2 = 0 ;
	}else if (x = 3) {
		OP1 = 1 ;
		OP2 = 1 ;
	}else {
	      //
	     // cout << "Invalid Operation Code./n";
	   }
	if ( -8 < y && y < 0) { // Given a decimal number, represents MSB digit
		D4 = 1;
	} 	else if ( -1 < y && y < 8) {
		D4 = 0	;
	}else {
	      // if a number that the ALU cannot handle is entered
	      //cout << "Invalid number./n";
	}
	if (( 3 < y && y < 8)|| (-5 < y && y < -0))	{ //represents second MSB digit
			D3 = 1 ;
	} else {
			D3 = 0;
	}
	if ( (1 < y && y < 4)|| (5 < y && y < 8) ||( -3 < y && y < 0)||( -7 < y && y < -4))	{ // represents second LSB digit
			D2 = 1 ;
	} else {
			D2 = 0 ;
	}
	if (y % 2 == 0){ //represents LSB digit
		D1= 0 ;
	}
	else {
		D1 = 1 ;
	}


	void clock_signal (int s);
	void clock_signal (int s) {
		z = 1;
		alarm(1);
		signal(SIGALRM, clock_signal);
	}



	if (z==1)
	{
		if(DATA == DATA_OUTPUTS-1)
		{
		DATA = 1;
	}
		else {
			DATA++;
		}
	}

	if (z==1)
		{
			if(OP_CODES == OP_CODE_COMMANDS-1)
			{
			OP_CODES = 1;
		}
			else {
				OP_CODES++;
			}
		}

	SI_SBIT(OP1, SFR_P0, 1); //setting the pins that correspond to each part of the opcode
	SI_SBIT(OP2, SFR_P0, 2);
	SI_SBIT(D1, SFR_P0, 3);
	SI_SBIT(D2, SFR_P0, 4);
	SI_SBIT(D3, SFR_P0, 5);
	SI_SBIT(D4, SFR_P0, 6);
	SI_SBIT(z, SFR_P0, 7);
	
	
}
