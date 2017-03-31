
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>                // SFR declarations
//#include "InitDevice.c"

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


void CLOCK(bool);
void DATA1(bool);
void DATA2(bool);
void DATA3(bool);
void DATA4(bool);
void OPCODE1(bool);
void OPCODE2(bool);

//void averagedelay(int);
int delay = 5000;
void averagedelay(){
	int z = 0;
	for(z=0;z<=delay;z++){
	}
}

void CLOCK(bool z){			//Clock Function
	P0_B7 = z;
}
void DATA1(bool z){			//Data 1 Function
	P0_B3 = z;
}
void DATA2(bool z){			//Data 2 Function
	P0_B4 = z;
}
void DATA3(bool z){			//Data 3 Function
	P0_B5 = z;
}
void DATA4(bool z){			//Data 4 Function
	P0_B6 = z;
}
void OPCODE1(bool z){		//OP Code 1 Function
	P0_B1 = z;
}
void OPCODE2(bool z){		//OP Code 2 Function
	P0_B2 = z;
}
void INSTRUCTIONSET(char opcode, char param) {
	averagedelay();			//Start Clock
	CLOCK(false);			//Stop Clock
	averagedelay();			//Continue Delay for Function
	DATA1(param & 1);		//Enter DATA for first bit
	DATA2(param & 2);		//Enter DATA for second bit
	DATA3(param & 3);		//Enter DATA for third bit
	DATA4(param & 4);		//Enter DATA for fourth bit
	OPCODE1(opcode & 1);	//Enter OPCODE for first bit
	OPCODE2(opcode & 2);	//Enter OPCODE for second bit
	averagedelay();			//Continue Delay
	CLOCK(true);			//Start Clock Again
	averagedelay();			//Delay for Computation
	CLOCK(false);			//Disable Clock
	averagedelay();			//Delay for Computation
	CLOCK(true);			//Start Clock Again
}

int main (void)
{	XBR2 |= 0x40;
	 INSTRUCTIONSET(0x00, 0x00);
	 INSTRUCTIONSET(0x03, 0x01);
	 INSTRUCTIONSET(0x01, 0x01);
	while (1) {}                             // Spin forever
}
