/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
// function_generator.c
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include <LED.h>
#include "bsp.h"
#include "tick.h"
#include "disp.h"
#include "render.h"
#include "thinfont.h"
#include "function_generator.h"
#include "square.h"
#include "waveform_tables.h"
#include "retargetserial.h"

int hour = 0;
int min = 0;
int sec = 0;
int hourprime = 0;
int minprime = 0;
int secprime = 0;
int on = 1;
int stop = 0;
int ms = 0;
///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////

// Generic line buffer
SI_SEGMENT_VARIABLE(Line[DISP_BUF_SIZE], uint8_t, RENDER_LINE_SEG);

// Demo state variables
// Frequency selection
#define SUPPORTED_NUM_FREQ 8
static SI_SEGMENT_VARIABLE(frequency[SUPPORTED_NUM_FREQ], uint16_t, SI_SEG_XDATA) = {
		1L,
		1L,
		1L,
		1L,
		1L,
		1L,
		1L,
		1L
};

// Current Frequency Selection
static uint8_t currentFreqIndex = 3;

// Phase offset (updated when frequency is changed)
static uint16_t phaseOffset = 100 * PHASE_PRECISION / SAMPLE_RATE_DAC;

// Kill splash
KillSpash killSplashFlag = SHOW_SPLASH;

///////////////////////////////////////////////////////////////////////////////
// Supporting Functions
///////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// drawScreenText
//-----------------------------------------------------------------------------
//
// Show one line of text on the screen
//
// str - pointer to string text (0 - 21 characters) to display
// rowNum - row number of the screen (0 - 127)
// fontScale - font scaler (1 - 4)
//
static void drawScreenText(SI_VARIABLE_SEGMENT_POINTER(str, char, RENDER_STR_SEG), uint8_t rowNum)
{
  uint8_t i;

  for (i = 0; i < FONT_HEIGHT; i++)
  {
    RENDER_ClrLine(Line);
    RENDER_StrLine(Line, 4, i, str);
    DISP_WriteLine(rowNum + i, Line);
  }
}

static void drawScreenTime(void)
{
  char hourStr[22];

  // display frequency on screen
  RETARGET_SPRINTF(hourStr, " TIME: %d : %d : %d ", hour, min, sec);

  drawScreenText(hourStr, 48);
}
static void drawScreenLap(void)
{
  char lapStr[22];

  // display frequency on screen
  RETARGET_SPRINTF(lapStr, " LAP:  %d : %d : %d ", hourprime, minprime, secprime);

  drawScreenText(lapStr, 58);
}
static void drawScreenMS(void)
{
  char msStr[22];

  // display frequency on screen
  RETARGET_SPRINTF(msStr, " Z :   %d ", ms);

  drawScreenText(msStr, 68);
}
//-----------------------------------------------------------------------------
// drawSplash
//-----------------------------------------------------------------------------
//
// Display splash screen with instructions.
//
static void drawSplash(void)
{
	uint16_t ticks = GetTickCount();

	drawScreenText(" __________________", 7);
	drawScreenText(" STOPWATCH", 4);


	while (((GetTickCount() - ticks) < 30) &&
			(killSplashFlag == SHOW_SPLASH)
			);
}

///////////////////////////////////////////////////////////////////////////////
// Interrupt Service Routines
///////////////////////////////////////////////////////////////////////////////

SI_INTERRUPT_USING (TIMER4_ISR, TIMER4_IRQn, 1)
{
  static uint16_t phaseAcc = 0;       // Holds phase accumulator

  SI_UU16_t temp;   // The temporary value that holds
									  // value before being written
									  // to the DAC
  
  TMR4CN0 &= ~TMR3CN0_TF3H__BMASK;    // Clear Timer4 overflow flag

  ms++;

  phaseAcc += phaseOffset;            // Increment phase accumulator

  // Read the table value
  temp.u16 = squareTable[phaseAcc >> 8];

  // Set the value of <temp> to the next output of DAC at full-scale
  // amplitude. The rails are 0x000 and 0xFFF. DAC low byte must be
  // written first.

  SFRPAGE = PG4_PAGE;

  DAC1L = DAC0L = temp.u8[LSB];
  DAC1H = DAC0H = temp.u8[MSB];
}

//-----------------------------------------------------------------------------
// PMATCH_ISR
//-----------------------------------------------------------------------------
//
// The Port Match interrupt occurs whenever (Pn & PnMASK) != (PnMAT & PnMASK).
// We must disable the interrupt and wait until the button is released in
// main, or else the interrupt will trigger multiple times.  It is generally
// not good practice to sit in an ISR for int32_t periods of time.
//
SI_INTERRUPT(PMATCH_ISR, PMATCH_IRQn)
{
	stop++;
	if(stop>4){
		stop=1;
	}
		hourprime = hour;
		minprime = min;
		secprime = sec;
		SFRPAGE = LEGACY_PAGE;              // EIE1 on SFRPAGE 0x00
		EIE1 &= ~0x02;
}

///////////////////////////////////////////////////////////////////////////////
// Driver Function
///////////////////////////////////////////////////////////////////////////////

void FunctionGenerator_main(void)
{

  DISP_ClearAll();

  while(1)
  {
	  if(on == 1){
	     if (ms < 30300){

	     }
	     else{
	    	 sec++;
	     }
	  	 if (sec == 60){
	  		 min++;
	  		 sec = 0;
	  	 }
	  	if (min == 60){
	  	  		 hour++;
	  	  		 min = 0;
	  	  	 }
	  }
	 drawSplash();
  	 drawScreenTime();
  	 drawScreenLap();
  }
}
