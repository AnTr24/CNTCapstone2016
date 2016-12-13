#include "derivative.h"

/*************************************************************
*                                                            *
*            Library:     7Seg_C.c                           *
*                                                            *
*             Author:     YunJie Li                          *
*                         CNT NAIT                           *
*                                                            *
*      Last Modified:     March 21, 2016 (Created)           *
*                                                            *
*************************************************************/

            
/*************************************************************
*                                                            *
*                      Char_7Seg_D                           *
*                                                            *
*        Requires:  A has position, B has char (both in      *
*                   lower nibble) Character has decimal      *
*         Returns:  None                                     *
*   Regs Affected:  None                                     *
*     Description:  Sends character in B to position in A    *
*                                                            *
**************************************************************

Char_7Seg_D:  pshd
            
              oraa  #$50          ; Hex Decoding, Decoding, Normal
              staa  PORTB         ; control for position
            
              ; ldaa  #$02          ; Write line low to write out the control,
              ; staa  PORTA         ; Mode is high throughout
              ; ldaa  #$03          ; Write line high again
              ; staa  PORTA
              
              bset  PORTA, #$02
              bclr  PORTA, #$01      
              bset  PORTA, #$03
              
              stab  PORTB         ; Character has NO decimal                                      
            
              ; ldaa  #$00          ; Write line low to write out the data
              ; staa  PORTA         ; Mode is low throughout
              ; ldaa  #$01          ; Write line high again
              ; staa  PORTA
              
              bclr  PORTA, #$03
              bset  PORTA, #$01
            
              puld
            
              rts
            
                       
            
            
;**************************************************************
;*                                                            *
;*                       ClearAll                           *
;*                                                            *
;*        Requires:  A has position, (in lower nibble)        *
;*                   Character has NO decimal                 *
;*         Returns:  None                                     *
;*   Regs Affected:  None                                     *
;*     Description:  Clear all segments of char in position A *  
;*                                                            *
;**************************************************************

Clear_7Seg: pshd
            
            oraa  #$70          ; Hex, No Decode, Normal
            staa  PORTB         ; control for position
            
            ; ldaa  #$02          ; Write line low to write out the control,
            ; staa  PORTA         ; Mode is high throughout
            ; ldaa  #$03          ; Write line high again
            ; staa  PORTA
            
            bset  PORTA, #$02
            bclr  PORTA, #$01      
            bset  PORTA, #$03
            
            ldab  #$80          ; Clear all the segments, no decimal
            stab  PORTB         ; using direct control of segments - turn
                                ; them all off with 0's in segments a-f                                      
            
            ; ldaa  #$00          ; Write line low to write out the data
            ; staa  PORTA         ; Mode is low throughout
            ; ldaa  #$01          ; Write line high again
            ; staa  PORTA
            
            bclr  PORTA, #$03
            bset  PORTA, #$01
            
            puld
            
            rts
*/

/*void Clear_7Seg() {
  PORTB |= 0x70;
  
  PORTA |= 0x02;
  PORTA &= 0xFE;
  PORTA |= 0x03;
  
  PORTB = 0x80;
  
  PORTA = 0x00;
  PORTA = 0x01;
  
  PORTA &= 0xFC;
  PORTA |= 0x01;
}      */
            
/*            
;**************************************************************
;*                                                            *
;*                    LEDS_7Seg_Init                          *
;*                                                            *
;*        Requires:  None                                     *
;*         Returns:  None                                     *
;*   Regs Affected:  None                                     *
;*                                                            *
;*     Description:  This is a set of instructions to clear   *
;*                   the memory of the 7 Segment LED digits   *
;*                   - used prior to writing anything to them *
;*                                                            *
;**************************************************************

LEDS_7Seg_Init:  

            psha
            pshb
            
            ldaa  #$03          ; Set lower 2 bits of porta
            staa  DDRA          ; and portb to outputs
            ldaa  #$ff
            staa  DDRB
            
            ; movb  #$03,PORTA    ; bring the mode and R/W high to get ready
            
            bset  PORTA,#$03
            
            clrb                ; lower 3 bits have the digit number
            orab #$70           ; Hex, No Decode, Normal
            
            ldaa  #$8           ; initialize a counter to control
                                ; the number of clears
                                
clearDig:   stab  PORTB         ; Set up to start clearing digits
                                ; starting at digit 0
                                
            ; movb  #$02,PORTA    ; load the control byte, this uses
            ; movb  #$03,PORTA    ; no decode mode, and writes 0s to
                                ; all the segments below
            
            bset  PORTA, #$02
            bclr  PORTA, #$01      
            bset  PORTA, #$03
            
                                
            movb  #$80,PORTB    ; Data for the clear - no decimals
            ; movb  #$00,PORTA    ; and toggle the R/W line for data
            ; movb  #$01,PORTA
            
            bclr  PORTA, #$03
            bset  PORTA, #$01
            
            incb                ; select next digit
            dbne  a,clearDig    ; repeat for all digits
            
            pulb
            pula                ; Note - R/W line left high on exit
            
            rts
*/           

void SevSegInit() {
  int i;
  
  DDRA = 0x03;
  DDRB = 0xFF;
  PORTA |= 0x03;
  PORTB = 0x70;
  for (i = 0; i < 8; i++) {                  
    PORTA |= 0x02;
    PORTA &= 0xFE;
    PORTA |= 0x03;
    
    PORTB = 0x80;
    
    PORTA &= 0xFC;
    PORTA |= 0x01;  
    PORTB++;
  }  
}

/*********************************************************
* Method:       ShowHexVal                               *                                        
* Accepts:      Position and Value                       *
* Description:  Display the value on the positions of    *
*               the 7 segment LEDs                       *
*********************************************************/  

void ShowHexVal(int pos, int val) {
  PORTB = 0x50 | pos;
  PORTA |= 0x02;
  PORTA &= 0xFE;
  PORTA |= 0x03;
  PORTB = 0x80 | val;
  PORTA &= 0xFC;
  PORTA |= 0x01;   
}

        
// Top 16 Out
void ShowTopSixteen(int val) {
  // Clear all positions
  int i;
  for (i = 0; i < 4; i++) {
    ShowHexVal(i, 0);
  }
  
  //for (i = 0; i < 4; i++) {
    
  ShowHexVal(3, val & 0x000F);
  ShowHexVal(2, (val & 0x00F0) >> 4);
  ShowHexVal(1, (val & 0x0F00) >> 8);
  ShowHexVal(0, (val & 0xF000) >> 12);
}


// Bottom 16 Out
void ShowBotSixteen(int val) {
  // Clear all positions
  int i;
  for (i = 4; i < 8; i++) {
    ShowHexVal(i, 0);
  }
  
  //for (i = 0; i < 4; i++) {
    
  ShowHexVal(7, val & 0x000F);
  ShowHexVal(6, (val & 0x00F0) >> 4);
  ShowHexVal(5, (val & 0x0F00) >> 8);
  ShowHexVal(4, (val & 0xF000) >> 12);
}


// Top 8 Out
void ShowTopEight(int val) {
  // Clear all positions
  
  ShowHexVal(2, 0);
  ShowHexVal(3, 0);
  
  
  //for (i = 0; i < 4; i++) {
    
  ShowHexVal(3, val & 0x000F);
  ShowHexVal(2, (val & 0x00F0) >> 4);

}


// Botttom 8 Out
void ShowBotEight(int val) {
  // Clear all positions

  ShowHexVal(7, 0);
  ShowHexVal(6, 0);
  
  //for (i = 0; i < 4; i++) {
    
  ShowHexVal(7, val & 0x000F);
  ShowHexVal(6, (val & 0x00F0) >> 4);

}