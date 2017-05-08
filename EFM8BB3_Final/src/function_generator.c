/**************************************************************************//**
 * Copyright (c) 2015 by Silicon Laboratories Inc. All rights reserved.
 *
 * http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
 *****************************************************************************/
///////////////////////////////////////////////////////////////////////////////
// function_generator.c
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

//TO DO
//Store Line as variable
//Scroll outputs variables in different order
	//Ex. if JOYSTICK_N  drawScreenText(row2, 1) drawScreenText(row3, 2) etc.
	//if array has 20 characters (uses 20 bytes) z+10
	//for normal input text writes on rowNum z

///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////

#include "bsp.h"
#include "tick.h"
#include "disp.h"
#include "render.h"
#include "square.h"
#include "joystick.h"
#include "thinfont.h"
#include "function_generator.h"
#include "waveform_tables.h"
#include "retargetserial.h"
#include <SI_EFM8BB3_Register_Enums.h>
#include "string.h"
///////////////////////////////////////////////////////////////////////////////
// Globals
///////////////////////////////////////////////////////////////////////////////
char outputstr[1];
char output[16] = {0};
int hextext;
int z;
char xdata savedinfo[26][16] = {0};
char xdata testbuffer[16] = {0};
int x;
char xdata outputbuffer[16];
int n;

// Generic line buffer
SI_SEGMENT_VARIABLE(Line[DISP_BUF_SIZE], uint8_t, RENDER_LINE_SEG);

// Demo state variables

// Frequency selection
#define SUPPORTED_NUM_FREQ 1
static SI_SEGMENT_VARIABLE(frequency[SUPPORTED_NUM_FREQ], uint16_t, SI_SEG_XDATA) = {
		10L
};

// Current Frequency Selection
static uint8_t currentFreqIndex = 1;

// Phase offset (updated when frequency is changed)
static uint16_t phaseOffset = 100 * PHASE_PRECISION / SAMPLE_RATE_DAC;

// Kill splash
KillSpash killSplashFlag = SHOW_SPLASH;

///////////////////////////////////////////////////////////////////////////////
// Supporting Functions
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// getJoystick
//-----------------------------------------------------------------------------
//
// Get new ADC sample and return joystick direction. Valid return values:
//  JOYSTICK_NONE   JOYSTICK_N   JOYSTICK_S
//  JOYSTICK_C      JOYSTICK_E   JOYSTICK_W
//
static uint8_t getJoystick(void)
{
  uint32_t mv;
  uint8_t dir;
  ADC0CN0_ADBUSY = 1;
  while (!ADC0CN0_ADINT);
  ADC0CN0_ADINT = 0;
  mv = ((uint32_t)ADC0) * 3300 / 1024;
  dir = JOYSTICK_convert_mv_to_direction(mv);
  return dir;
}

//-----------------------------------------------------------------------------
// getWaitJoystick
//-----------------------------------------------------------------------------
//
// Get joystick input. If joystick was moved, wait for release. Return joystick
// direction. Valid return values:
//  JOYSTICK_NONE   JOYSTICK_N   JOYSTICK_S
//  JOYSTICK_C      JOYSTICK_E   JOYSTICK_W
//
static uint8_t getWaitJoystick(void)
{
  uint8_t dir, dirSave;

  dir = getJoystick();
  dirSave = dir;

  // wait for release then transition
  while (dir != JOYSTICK_NONE)
  {
    dir = getJoystick();
  }

  return dirSave;
}

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
static void drawSplash(void)
{
	uint16_t ticks = GetTickCount();

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
// INT0_ISR
//-----------------------------------------------------------------------------
//
// INT0 ISR Content goes here. Remember to clear flag bits:
// TCON::IE0 (External Interrupt 0)
//
// Whenever a negative edge appears on P0.2, toggle LED_GREEN.
// The interrupt pending flag is automatically cleared by vectoring to the ISR
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (INT0_ISR, INT0_IRQn)
{
	hextext = 1;
}


//-----------------------------------------------------------------------------
// INT1_ISR
//-----------------------------------------------------------------------------
//
// INT1 ISR Content goes here. Remember to clear flag bits:
// TCON::IE1 (External Interrupt 1)
//
// Whenever a negative edge appears on P0.3, toggle LED_BLUE.
// The interrupt pending flag is automatically cleared by vectoring to the ISR
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (INT1_ISR, INT1_IRQn)
{
	hextext = 0;
}
int m;
int i;
int y;
//FUNCTIONS
static void Scroll(void){
	DISP_ClearAll();
    for(n = y; n <17; n++){
	memcpy(outputbuffer, savedinfo[n], 16);
	drawScreenText(outputbuffer, m);
    m+=8;
    //}
}
}

static void processScroll(uint8_t dir)
{
  // process input
  if (dir == JOYSTICK_S)
  {
	 y--;
	 Scroll();
  }
  if (dir == JOYSTICK_N)
  {
	 y++;
	 Scroll();
  }
}

int j = 0;
int k = 0;
///////////////////////////////////////////////////////////////////////////////
// Driver Function
///////////////////////////////////////////////////////////////////////////////

void FunctionGenerator_main(void)
{
  unsigned char inputchar;
  hextext = 0;
  z = 0;
  x = 0;
  i = 0;
  n = 0;
  y = 0;
  DISP_ClearAll();
  SCON0_TI = 1;
  while(1)
  {
	  drawSplash();
	  RETARGET_PRINTF ("\nEnter character: ");
      inputchar = getchar();
      RETARGET_PRINTF ("\nCharacter entered: %c", inputchar);
      RETARGET_PRINTF ("\n     Value in Hex: %bx", inputchar);
	  if(hextext == 0){
		  RETARGET_SPRINTF (outputstr, "%c", inputchar);
		  strcat(output,&outputstr);
		  i=strlen(output);
		  strcat(savedinfo[x],&outputstr);
		  if(i>16){
			  z+=8;
			  x++;
			  i = 0;
			  memset(output,0,16);
			  strcat(output,&outputstr);
		  }
      	  }
      if(hextext == 1){
    	  RETARGET_SPRINTF (outputstr, "%bx", inputchar);
    	  strcat(output,&outputstr);
    	  i=strlen(output);
    	  if(i>16){
    		  z+=8;
    		  i = 0;
    		  memset(output,0,16);
    		  strcat(output,&outputstr);
    	  }
      	  }
      drawScreenText(output,z);
      processScroll(getWaitJoystick());
  }
}


