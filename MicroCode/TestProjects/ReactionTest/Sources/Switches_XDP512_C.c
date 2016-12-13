#include "derivative.h"
#include "Delay_C.h"

/*
;Library: Switches_XDP512_C.c
;
;Decription: Library for the 5 switches
;
;Author:  Andy Tran
;
;Requires: Delay Subroutine
;
;Last Modified:   March 11, 2016
;___________________________________________________
;
*/
/*
*************************************************************
*Function: 		Switch_Check
				
*
*Description:	Switch Action Code. To be sent to main
************************************************************
*/
/*
void Switch_Check(void)
{
    unsigned char Sw_states = Get_Switches();
    
    if(Sw_states)					    //optional: wait for switches up				
	    Wait_For_Switches_Up();         //before running switch actions
	    
	switch(Sw_states)
	{
		case 0x10:
		break;
		
		case 0x08:
		break;
		
		case 0x04:
		break;
		
		case 0x02:
		break;
		
		case 0x01:
		break;
	}
}
*/
/*
*************************************************************
*Function: 		Sw_Init
*
*Description:	Initializes port lines associated with the
*				switches by placing 1 in appropriate positions
*************************************************************
*/
void Sw_Init(void)
{
	ATD1DIEN1 |= 0x1F;
}
/*
*************************************************************
*Function: 		Wait_For_Switches_Up
*
*Description:	Hangs in a loop until all switches are released
*************************************************************
*/
void Wait_For_Switches_Up(void)
{
	unsigned char Switches = 0;
	Switches = PT1AD1 & 0x1F; //filter LEDs
	
	while(Switches)	//loop as long as any switches are down(1)
		{
		    Switches = PT1AD1 & 0x1F;
		}
}
/*
*************************************************************
*Function: 		Get_Switches()
*
*Description:	Returns an unsigned char that contains bit
*postions of switches that are down after debouncing.
*Returns 0 if switches are unstable
*************************************************************
*/
unsigned char Get_Switches(void)
{
	unsigned char Switches = 0;
	Switches = PT1AD1 & 0x1F;	//Filter out LEDs
	
	Delay_C(10);	//Debounce (10 ms)
	
	if((PT1AD1 & 0x1F) != Switches)	//If current value is not
		Switches = 0;				//the same as old values then	
									//switches are unstable
																		
	return Switches;                
}





                                                                                                                      