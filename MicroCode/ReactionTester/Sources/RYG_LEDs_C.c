#include    "derivative.h"


/*;Library: LEDS_RYG_XDP512.inc
;
;Contains:
;
;     Red_On
;     Red_Off
;     Red_Toggle
;
;     Yellow_On
;     Yellow_Off
;     Yellow_Toggle
;
;     Green_On
;     Green_Off
;     Green_Toggle
;
;     led_sw_init
;
;Author:  Andy Tran
;
;Last Modified:   January 13, 2016
;___________________________________________________
;
;___________________________________________________
;
;              LED_init
;
;Requires:      None
;Returns:       None 
;Regs Affected: None
;
;Description:   This routine initializes the upper half
;                of portad for the RYG LEDs 
;___________________________________________________________
*/
               
void LED_Init(void)
{
    PT1AD1  &=  0x1F;    //all LEDs off at the start
                        //no unpredictable behaviour
    
    DDR1AD1 |=  0xE0;   //make all LEDs outputs, rest inputs
}
/*;___________________________________________________
;
;              Red On-Off-Toggle Subroutines
;
;Requires:      None
;Returns:       None 
;Regs Affected: None
;
;___________________________________________________________                
                            
 Red_On:    psha
            pshb
            
            ldd PT1AD1
            oraa    #%10000000
            std PT1AD1
            
            
            pulb
            pula
            rts 

Red_Off:    psha
            pshb
            
            ldd PT1AD1
            anda    #%01111111
            std PT1AD1
            
            pulb
            pula
            rts

Red_Toggle: psha
            pshb
            
            ldd PT1AD1
            EORA    #%1000
            std PT1AD1
            
            pulb
            pula
            rts    */
            
void Red_On(void)
{
    PT1AD1  |=  0x80;    
}

void Red_Off(void)
{
    PT1AD1  &=  0x7F;    
}

void Red_Toggle(void)
{
    PT1AD1  ^=  0x80;    
}

/*;___________________________________________________
;
;              Yellow On-Off-Toggle Subroutines
;
;Requires:      None
;Returns:       None 
;Regs Affected: None
;
;___________________________________________________________                
                            
 Yellow_On: psha
            pshb
            
            ldd PT1AD1
            oraa    #%01000000
            std PT1AD1
            
            
            pulb
            pula
            rts 

Yellow_Off: 
            psha
            pshb
            
            ldd PT1AD1
            anda    #%10111111
            std PT1AD1
            
            pulb
            pula
            rts

Yellow_Toggle: psha
            pshb
            
            ldd PT1AD1
            EORA    #%0100
            std PT1AD1
            
            pulb
            pula
            rts */

void Yellow_On(void)
{
    PT1AD1  |=  0x40;    
}

void Yellow_Off(void)
{
    PT1AD1  &=  0xBF;    
}

void Yellow_Toggle(void)
{
    PT1AD1  ^=  0x40;    
}

/*;___________________________________________________
;
;              Green On-Off-Toggle Subroutines
;
;Requires:      None
;Returns:       None 
;Regs Affected: None
;
;___________________________________________________________                
                            
Green_On:   psha
            pshb
            
            ldd PT1AD1
            oraa    #%00100000
            std PT1AD1
            
            
            pulb
            pula
            rts 

Green_Off:  psha
            pshb
            
            ldd PT1AD1
            anda    #%11011111
            std PT1AD1
            
            pulb
            pula
            rts

Green_Toggle: 
            psha
            pshb
            
            ldd PT1AD1
            EORA    #%0010
            std PT1AD1
            
            pulb
            pula
            rts*/
       
void Green_On(void)
{
    PT1AD1  |=  0x20;    
}

void Green_Off(void)
{
    PT1AD1  &=  0xDF;    
}

void Green_Toggle(void)
{
    PT1AD1  ^=  0x20;    
}