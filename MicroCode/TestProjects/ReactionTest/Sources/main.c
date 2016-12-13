#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Delay_C.h"
#include "LCD_4Line_C.h"
#include "RYG_LEDs_C.h"
#include "Switches_XDP512_C.h"
#include "LEDS_7Seg_C.h"
#include "stdio.h"
#include <time.h> 
#include <stdlib.h>

  char TFOCount;
  char s[20];
  unsigned int randTime;
  unsigned char bReady = 0; 

void main(void) {
  //Variables
  unsigned char sw_state = 0;
  
  //Initializations
  Sw_Init();
  LED_Init();
  lcdInit();
  LEDS_7Seg_Init();

  /* put your own code here */

  TSCR1 = 0b10000000;         //Turn timer on
  TSCR2 &= 0b11111000;        //clear prescaler bits   
  TSCR2 |= 0b00000110;        //set prescaler  x64
  TIOS |= 0b00000001;         //TIOS0 set to output compare
  TCTL2 &= 0b11111100;        //Cleairng bits for output to PT0
  TCTL2 |= 0b00000001;        //Set low bit for TC0 for toggle(01) on PT0
  TIE |= 0b00000001;          //enable channel 0 for interrupts
  TFLG1 = 0b00000001;         //clear TC0 flag
  TC0 = TCNT +125;            //set interval: every 1ms
  EnableInterrupts;
  
  
  Set_R_C(0,0);
  lcdString("When ready:");
  Set_R_C(1,0);
  lcdString("Press top switch.");

  for(;;) 
  {
    sw_state = Get_Switches();
    if(sw_state == 0x10)   //Top switch, so user is ready.
    {
       bReady = 1;
    }
    
    if(bReady) 
    {
      lcdClear(); 
      Set_R_C(0,0);
      lcdString("When light is green:");
      Set_R_C(1,0);
      lcdString("Press center switch.");
  
      Red_On();
      srand(TCNT);  //rand generator seeding
      randTime = rand() % 3000 + 2000;   //time will be between 2-5 seconds
    }
    
    
     asm WAI;
  } /* loop forever */
  /* please make sure that you never leave main */
}

interrupt VectorNumber_Vtimch0 void TimerInterval(void) 
{
    TFLG1 = 0b00000001;
    
    if(randTime) 
    {
      randTime--;
    }
    
    if(randTime==0 && bReady)
    {
      Green_On();
    }
    TC0 = TCNT +125;
}
