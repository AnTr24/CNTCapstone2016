#include "derivative.h"
#include "Delay_C.h"

/*
;**************************************************************
;*                                                            *
;*                                                            *
;*            Library:     Switches_C                          *
;*                                                            *
;*           Contains:     Sw_Init                            *
;*                                                            *
;*                         Get_Switches                       *
;*                         Wait_for_Switches_up               *
;*                                                            *
;*             Author:     YunJie Li                          *
;*                         CNT NAIT                           *
;*                                                            *
;*      Last Modified:     March 14, 2016 (Created)           *
;*                                                            *
;*                                                            *
;**************************************************************


;**************************************************************
;*                                                            *
;*    Function:     Sw_Init()                                 *
;*    Description:  This function initializes the port lines  *
;*                  associated with the switches by placing 1 *
;*                  in the appropriate bit pos of ATD1DIEN1   *
;*                                                            *
;**************************************************************
*/

void Sw_Init() {
  ATD1DIEN1 |= 0x1F;    // Enable the inputs for the switches
}

/*
;**************************************************************
;*                                                            *
;*    Function:     Get_Switches()                            *
;*    Description:  This function returns an unsigned char    *
;*                  that contains ones in the bit pos of the  *
;*                  switches that are down, after debouncing. *
;*                  If the switches are not stable, the func  *
;*                  just return zero.                         * 
;*                                                            *
;**************************************************************
*/

unsigned char Get_Switches() {
  unsigned char Switches = 0;
  
  Switches = PT1AD1 & 0x1F;
  Delay_C(10);                // A 10 msec decounce
  
  if ((PT1AD1 & 0x1F) != Switches)
    Switches = 0;
    
  return Switches;
}

/*
;**************************************************************
;*                                                            *
;*    Function:     Wait_for_Switches_up(void)                *
;*    Description:  This function hangs in a loop waiting for *
;*                  all the switches to be in the up state.   *
;*                                                            *
;**************************************************************
*/

void Wait_for_Switches_up() {
  unsigned char Switches = 0;
  
  Switches = PT1AD1 & 0x1F;
  
  // Do I need to debounce this?
  
  while (Switches) {
    Delay_C(10);
    Switches = PT1AD1 & 0x1F;
    
  }
}




























