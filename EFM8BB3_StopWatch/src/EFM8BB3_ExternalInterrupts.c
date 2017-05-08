//-----------------------------------------------------------------------------
// EFM8BB3_ExternalInterrupts.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This software shows the necessary configuration to use External Interrupt 0
// (/INT0) or External Interrupt 1 (/INT1) as an interrupt source.  The code
// executes the initialization routines and then spins in an infinite while()
// loop.  If the right button is pressed, then the edge-triggered /INT0 input
// on P0.2 will cause an interrupt and toggle LED_GREEN. If the left button
// is pressed,then the edge-triggered /INT1 input on P0.3 will cause an
// interrupt and toggle the LED_BLUE.
//
// Resources:
//   SYSCLK - 24.5 MHz HFOSC0 / 1
//   P0.2   - Push button switch, /INT0 input
//   P0.3   - Push button switch, /INT1 input
//   P1.4   - LED green
//   P1.5   - LED blue
//   P3.4   - Display enable
//
//-----------------------------------------------------------------------------
// How To Test: EFM8BB3 STK
//-----------------------------------------------------------------------------
// 1) Place the switch in "AEM" mode.
// 2) Connect the EFM8BB3 STK board to a PC using a mini USB cable.
// 3) Compile and download code to the EFM8BB3 STK board.
//    In Simplicity Studio IDE, select Run -> Debug from the menu bar,
//    click the Debug button in the quick menu, or press F11.
// 4) Run the code.
//    In Simplicity Studio IDE, select Run -> Resume from the menu bar,
//    click the Resume button in the quick menu, or press F8.
// 5) Press the switches.  Every time a switch is pressed, one of
//    the LEDs should toggle.
//
// Target:         EFM8BB3
// Tool chain:     Generic
//
// Release 0.1 (ST)
//    - Initial Revision
//    - 20 MAY 2015
//

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include <SI_EFM8BB3_Register_Enums.h>
#include "InitDevice.h"
#include "bsp.h"
#include "tick.h"
#include "disp.h"
#include "render.h"

// Generic line buffer
SI_SEGMENT_VARIABLE(Line[DISP_BUF_SIZE], uint8_t, RENDER_LINE_SEG);
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
//-----------------------------------------------------------------------------
// Pin Definitions
//-----------------------------------------------------------------------------
SI_SBIT (DISP_EN, SFR_P3, 4);          // Display Enable
#define DISP_BC_DRIVEN   0             // 0 = Board Controller drives display
#define DISP_EFM8_DRIVEN 1             // 1 = EFM8 drives display

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main (void)
{
   enter_DefaultMode_from_RESET();

   DISP_EN = DISP_BC_DRIVEN;           // EFM8 does not drive display

   IE_EA = 1;

   if(sec == 60){
	min++;
	sec = 0;
}

   if(min == 60){
	hour++;
	min = 0;
}
   //LCD DISPLAY

   drawScreenText(hour, 4);
   drawScreenText(min, 5);
   drawScreenText(sec, 6);
   drawScreenText(hourprime1, 7);
   drawScreenText(minprime1, 8);
   drawScreenText(secprime1, 9);

   while(1);                           // Infinite while loop waiting for
                                       // an interrupt from /INT0 or /INT1
}
