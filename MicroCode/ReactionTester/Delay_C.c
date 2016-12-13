/*
;**************************************************************
;*                                                            *
;*                                                            *
;*            Library:     My Delays.inc                      *
;*                                                            *
;*           Contains:     Delay                              *
;*                                                            *
;*             Author:     YunJie Li                          *
;*                         CNT NAIT                           *
;*                                                            *
;*      Last Modified:     Jan 13, 2016 (Created)             *
;*                                                            *
;*                                                            *
;**************************************************************


;**************************************************************
;*                                                            *
;*                Delay       Subroutine                      *
;*                                                            *
;*        Requires:     Number of msec specified in x         *
;*         Returns:     None                                  *
;*   Regs Affected:     Trashes Y                             *
;*     Description:     This performs a delay of the number   *
;*                      of msec specified by the x register   *
;*                                                            *
;**************************************************************



Delay:      ldy #2665        ;inside loop counter
delay_2:    dbne y, delay_2
            dbne x, Delay
                
            rts           
*/

void Delay_C(int mSec) {
  asm ldx mSec
  asm Delay:    ldy #2665       // inside loop counter
  asm delay_2:  dbne y, delay_2
  asm dbne x, Delay
}