#include "derivative.h"

/*
;**************************************************************
;*                                                            *
;*                                                            *
;*            Library:     LEDS_RYG_XDP512.inc                *
;*                                                            *
;*           Contains:     led_sw_init                        *
;*                                                            *
;*                         Red_On                             *
;*                         Red_Off                            *
;*                         Red_Toggle                         *
;*                                                            *
;*                         Yellow_On                          *
;*                         Yellow_Off                         *
;*                         Yellow_Toggle                      *
;*                                                            *
;*                         Green_On                           *
;*                         Green_Off                          *
;*                         Green_Toggle                       *
;*                                                            *
;*             Author:     YunJie Li                          *
;*                         CNT NAIT                           *
;*                                                            *
;*      Last Modified:     Jan 13, 2016 (Created)             *
;*                                                            *
;*                                                            *
;**************************************************************



;**************************************************************
;*            led_sw_init     Subroutine                      *
;*                                                            *
;*    Description:     This routine initializes the upper     *
;*                     half of ported for the RYG LEDS        *
;*                     and the switches                       *
;**************************************************************

led_sw_init:  bclr PT1AD1,#$E0            ; make all leds low
              bset DDR1AD1, #$E0          ; make PAD13:15 outputs, rest inputs
              bset ATD1DIEN1,#$1F         ; enable digital inputs for switches  ATD1:Lo
              
              rts
*/

void led_sw_init(void) {
  PT1AD1 &= 0x1F;     // all the LEDs off at the start
                      // no unpredictable behavior
  DDR1AD1 |= 0xE0;    // make all LEDs outputs, reset inputs
  ATD1DIEN1 |= 0x1F;  // enable digital inputs for switches
}

/*
;**************************************************************
;*            Red_On/Off/Toggle     Subroutines               *
;**************************************************************

Red_On:       psha
              pshb
              
              ldd PT1AD1
              oraa #%10000000
              std PT1AD1
              
              pulb
              pula
              rts

Red_Off:      psha
              pshb
              
              ldd PT1AD1
              anda #%01111111
              std PT1AD1
              
              pulb
              pula
              rts

Red_Toggle:   psha
              pshb
              
              ldd PT1AD1
              eora #%10000000
              std PT1AD1
              
              pulb
              pula
              rts
*/

void Red_On(void) {
  PT1AD1 |= 0x80;
}

void Red_Off(void) {
  PT1AD1 &= 0x7F;
}

void Red_Toggle(void) {
  PT1AD1 ^= 0x80;
}

/*
;**************************************************************
;*           Yellow_On/Off/Toggle     Subroutines             *
;**************************************************************

Yellow_On:      psha
                pshb
              
                ldd PT1AD1
                oraa #%01000000
                std PT1AD1
              
                pulb
                pula
                rts

Yellow_Off:     psha
                pshb
              
                ldd PT1AD1
                anda #%10111111
                std PT1AD1
              
                pulb
                pula
                rts

Yellow_Toggle:  psha
                pshb
              
                ldd PT1AD1
                eora #%01000000
                std PT1AD1
              
                pulb
                pula
                rts               
*/

void Yellow_On(void) {
  PT1AD1 |= 0x40;
}

void Yellow_Off(void) {
  PT1AD1 &= 0xBF;
}

void Yellow_Toggle(void) {
  PT1AD1 ^= 0x40;
}

/*
;**************************************************************
;*           Green_On/Off/Toggle     Subroutines              *
;**************************************************************

Green_On:     psha
              pshb
              
              ldd PT1AD1
              oraa #%00100000
              std PT1AD1
              
              pulb
              pula
              rts

Green_Off:    psha
              pshb
              
              ldd PT1AD1
              anda #%11011111
              std PT1AD1
              
              pulb
              pula
              rts

Green_Toggle: psha
              pshb
              
              ldd PT1AD1
              eora #%00100000
              std PT1AD1
              
              pulb
              pula
              rts            
*/

void Green_On(void) {
  PT1AD1 |= 0x20;
}

void Green_Off(void) {
  PT1AD1 &= 0xDF;
}

void Green_Toggle(void) {
  PT1AD1 ^= 0x20;
}


