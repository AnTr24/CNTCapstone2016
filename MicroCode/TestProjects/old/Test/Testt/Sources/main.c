#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Delay_C.h"
#include "LCD_4Line_C.h"
#include "Switches_XDP512_C.h"
#include "stdio.h"
#include "LEDS_7Seg_C.h"


void main(void) {
  /* put your own code here */
  char s[20];
  float fRuntime = 0.0;
  
  lcdInit();
  Sw_Init();
  LEDS_7Seg_Init();
  
  TSCR1 = 0b10000000;         //Turn timer on
  TSCR2 &= 0b11111000;        //clear prescaler bits   
  TSCR2 |= 0b00000110;        //set prescaler  x64
  TIOS |= 0b00000001;         //TIOS0 set to output compare
  TCTL2 &= 0b11111100;        //Cleairng bits for output to PT0
  TCTL2 |= 0b00000001;        //Set low bit for TC0 for toggle(01) on PT0
  TIE |= 0b00000001;          //enable channel 0 for interrupts
  TFLG1 = 0b00000001;         //clear TC0 flag
  TC0 = TCNT + 125;           //set interval

  EnableInterrupts;
  
  Set_R_C(0,0);
  lcdString("Time Running: ");

  for(;;) {
    
    Set_R_C(1,0); 
    if(sprintf(s,"%4.3f",fRuntime)>=0)
            lcdString(s);
    
   
    asm WAI;
    fRuntime+=0.001;    
  } 
  
}

interrupt VectorNumber_Vtimch0 void TimerInterval(void) 
{
    TFLG1 = 0b00000001; 
    TC0 += 125;
}