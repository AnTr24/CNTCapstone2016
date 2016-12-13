#include "derivative.h"
#include "LEDS_7Seg_C.h"

/*Library: LEDS_7Seg.inc
;
;Contains:
;         LEDS_7Seg_Init
;         Char_7Seg
;         Char_7Seg_D
;         Clear_7Seg
;         Seg_Write
;         Top_8Out
;         Top_16Out
;         Bot_8Out
;         Bot_16Out
;     
;
;Author:  Andy Tran
;
;Last Modified:   February 08, 2016
;___________________________________________________*/

/*;___________________________________________________
;
;              LEDS_7Seg_Init
;
;Requires:      None
;Returns:       None 
;Description:   This is a set on isntrucyions to clear the memory
;                of the 7 Segment LED digits - used prior to writing to them
;___________________________________________________________*/

void LEDS_7Seg_Init(void)
{
    unsigned char control = 0x70;
    unsigned char i;
    
	DDRA = 0x03;	//Set lower 2 bits of PORTA
	DDRB = 0xFF;  	//and  all of PORTB to outputs
	
	PORTA = 0x03;	//bring the mode and R/W high to get ready
	
	for(i = 0; i < 8;i++)
	{
		PORTB = control;	//Set up to start clearing bits
                            //starting at digit 0
		
		PORTA = 0x02;		//load the control byte, this uses
		PORTA = 0x03;		//no decode mode, and writes 0s to
                            //all the segments below
							
		PORTB = 0x80;		//Data for the clear - no decimals
		PORTA = 0;			//and toggle for R/W line for data
		PORTA = 0x01;
		
		control++;
	}	
}

/*;___________________________________________________
;
;              Char_7Seg
;
;Requires:      2 arguments
;				
;Returns:       None 
;
;Description:   Sends character on val to position pos
;				(both lower nibble)
;___________________________________________________________*/

void Char_7Seg(unsigned char val,unsigned char pos)
{

	PORTB = pos | 0x50;	//Hex Decoding,Decoding,Normal + position
	
	PORTA |= 0x02;		//Write line low to write out the control
	PORTA &= 0xFE;      //Mode is high throughout
			
	PORTA |= 0x03;		//Write line high again
	
	PORTB = val | 0x80; //Character has NO decimal
	
	PORTA &= 0xFC;		//Write line low to write out the control,
						//Mode is low throughout
	PORTA |= 0x01;		//Write line high again
}

/*;___________________________________________________
;
;              Char_7Seg_D
;
;Requires:      2 arguments
;				
;Returns:       None 
;
;Description:   Sends character with decimal on val to 
;				position pos (both lower nibble)
;___________________________________________________________*/
void Char_7Seg_D(unsigned char val, unsigned char pos)
{
	PORTB = pos | 0x50;	//Hex Decoding,Decoding,Normal + position
	
	PORTA |= 0x02;		//Mode is high throughout
	PORTA &= 0xFE;		//Write line low to write out the control,
	
	PORTA |= 0x01;		//Write line high again
	
	PORTB = val;		//Character has decimal
	
	PORTA &= 0xFC;		//Write line low to write out the control,
						//Mode is low throughout
	PORTA |= 0x01;		//Write line high again
}

/*;___________________________________________________
;
;              Clear_7Seg
;
;Requires:      1 Argument: pos has a position	(lower nibble)
;				Character has NO decimal
;Returns:       None 
;Regs Affected: None
;
;Description:   Clears all segments of char in position pos
;___________________________________________________________*/
void Clear_7Seg(unsigned char pos)
{
	PORTB = pos | 0x70;	//Hex Decoding,No Decoding,Normal + position
	
	PORTA &= 0xFE;		//Write line low to write out the control,
	PORTA |= 0x02;		//Mode is high throughout
	PORTA |= 0x01;		//Write line high again
	
	PORTB = 0x80;		//clear all the segments, no decimal
						//using direct control of segments
						//Turn them all off with 0's in segemnts a-f
	
	PORTA &= 0xFC;		//Write line low to write out the control,
						//Mode is low throughout
	PORTA |= 0x01;		//Write line high again	
}

/*;___________________________________________________
;
;              Top_8Out
;
;Requires:      data has the input characters
;Returns:       None 
;Regs Affected: None
;
;Description:   Sends character on data to 7Segs LEDs 3&4. Blanks 0  and 1.
;___________________________________________________________*/
void Top_8Out(unsigned char data)
{
	Clear_7Seg(0);	//Clearing leds 0 and 1
	Clear_7Seg(1);
	
	Char_7Seg(data,3);	//Set the 3rd led 
	data = data >> 4;	//Rotate b 4 times to get at upper nibble/value
	Char_7Seg(data,2);	//Set the 2nd led 
}

/*;___________________________________________________
;
;              Bot_8Out
;
;Requires:      data has the input characters
;Returns:       None 
;Regs Affected: None
;
;Description:   Sends character on data to 7Segs LEDs 3&4. Blanks 0  and 1.
;___________________________________________________________*/
void Bot_8Out(unsigned char data)
{
	Clear_7Seg(4);	//Clearing leds 0 and 1
	Clear_7Seg(5);
	
	Char_7Seg(data,7);	//Set the 7th led 
	data = data >> 4;	//Rotate b 4 times to get at upper nibble/value
	Char_7Seg(data,6);	//Set the 6th led 
}

/*;___________________________________________________
;
;              Top_16Out
;
;Requires:      data has the input characters
;Returns:       None 
;Regs Affected: None
;
;Description:   Sends character on data to the top 4 7Segs LEDs
;___________________________________________________________*/
void Top_16Out(unsigned int data)
{
	Char_7Seg(data,3);	//Set the [3] led 
	
	data = data >> 4;	//Rotate b 4 times to get at upper nibble/value
	Char_7Seg(data,2);	//Set the [2] led 
	
	data = data >> 4;
	Char_7Seg(data,1);	//Set the [1] led 
	
	data = data >> 4;
	Char_7Seg(data,0);	//Set the [0] led 
}

/*;___________________________________________________
;
;              Bot_16Out
;
;Requires:      data has the input characters
;Returns:       None 
;Regs Affected: None
;
;Description:   Sends character on data to the top 4 7Segs LEDs
;___________________________________________________________*/
void Bot_16Out(unsigned int data)
{
	Char_7Seg(data,7);	//Set the [7] led 
	
	data = data >> 4;	//Rotate b 4 times to get at upper nibble/value
	Char_7Seg(data,6);	//Set the [6] led 
	
	data = data >> 4;
	Char_7Seg(data,5);	//Set the [5] led 
	
	data = data >> 4;
	Char_7Seg(data,4);	//Set the [4] led 
}