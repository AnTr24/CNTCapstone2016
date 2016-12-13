/* ;Library: Delay_C.c
;
;Contains:
;
;     Delay
;
;Author:  Andy Tran
;
;Last Modified:   March 07, 2016
;___________________________________________________
;
;___________________________________________________
;
;              Delay Subroutine
;
;Requires:      Number of msec specified in X (decimal)
;Returns:       None 
;Regs Affected: Trashes Y and decrements X to 0
;
;Description:   This preforms a delay of the number 0of ms specified
;                by the X register.
;___________________________________________________________


Delay:      ldy #2665

delay_2:    dbne y, delay_2
             dbne x, Delay
             
             rts
*/

void Delay_C (int mSec) 
{
    asm ldx mSec
    asm Delay:      ldy #2665
    asm delay_2:    dbne y, delay_2
    asm                 dbne x, Delay    
}

