#include "derivative.h"


/*
;Library: SCI_LIB_C.c
;
;Decription: Library for SCI
;
;
;Contains:      Rx_Byte
;               SCI_19200
;               Tx_Byte
;               Tx_String
;               TxSCI_String_B
;
;
;Author:  Andy Tran
;
;Requires: None
;
;Last Modified:   April 13, 2016
;___________________________________________________
;
*/

/*
*************************************************************
*Function: 		Key_hit
*
*Requires:      None
*
*Returns:       Returns SCI0SR1 & 0x20
*               This is checking RDRF
*               
*
*Description:	RDRF:
*                   =0x20 if a character is waiting
*                   =0x00 if no character is in   
*************************************************************
*/
unsigned char Key_hit(void)
{
    unsigned char ucKey_In = 0;
    ucKey_In = SCI0SR1 & 0x20;
    
    return ucKey_In; 	
}

/*
*************************************************************
*Function: 		Rx_Byte
*
*Requires:      None
*
*Returns:       ASCII from keyboard press
*               
*
*Description:	Polls RDRF(Receive Data Register Full Flag)
*               of SCI0SR1 until character is received.  
*************************************************************
*/
unsigned char Rx_Byte(void)
{
    while(!Key_hit());
    
    return SCI0DRL;	
}

/*
*************************************************************
*Function: 		SCI_19200
*
*Requires:      None
*
*Returns:       None
*               
*
*Description:	Initializes SCI for 19200 Baud, 8N1  
*************************************************************
*/
void SCI_19200(void)
{
    SCI0BDH = 0;
    SCI0BDL = 26;
    SCI0CR1 = 0x00;
    SCI0CR2 = 0x0C;
    	
}

/*
*************************************************************
*Function: 		Tx_Byte
*
*Requires:      character
*
*Returns:       None
*               
*
*Description:	Character to be sent is passed into function
*               as unsigned char. The transmit register is
*               checked until it is empty prior to writing the
*               character into it
*************************************************************
*/
void Tx_Byte(unsigned char cVal)
{
    while((SCI0SR1 & 0x80)==0); //wait until transmite register
    	                        //is empty
    	                        
    SCI0DRL = cVal;   	                        
}

/*
*************************************************************
*Function: 		Tx_String
*
*Requires:      string
*
*Returns:       None
*               
*
*Description:	Expects a string pointer. Calls Tx_Byte to transmit
*               each character/element of the string. Also
*               checks for end of string.
*************************************************************
*/
void Tx_String(char * cString)
{
    while(*cString !=0){
      Tx_Byte(*cString++);      //walk the pointer   
    }  	                        
}







                                                                                                                      