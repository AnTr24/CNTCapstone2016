#include "derivative.h"
#include "LCD_4Line_C.h"

/*-----------------------------------------------------------------
Library: LCD_4Line_C.c

Contains:	
		lcdInit

		lcdRWUp
		lcdRWDown
		
		lcdEUp
		lcdEDown
		
		lcdRSUp
		lcdRSDown
		
		lcdSDelay
		lcdLDelay
		
		lcdData
		lcdBusy
		lcdInst
		
		lcdAddr
		lcdCGAddr
		lcdString
		lcdClear
		
		Set_R_C
		lcdLabels
		
-----------------------------------------------------------------*/
/*-----------------------------------------------------------------
				lcdInit
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Initialize LCD (pu,reset init)			
--------------------------------------------------------------*/
void lcdInit(void)
{
	PTH = 0x00;			//premark all outputs as low
	DDRH = 0xFF;		//set port H as all outputs
	
	PORTK &= ~0x07;		//premark control outputs as low (A=R/W*=E=0)
	DDRK |= 0x07;		//set port K0:2 as outputs
	
						//All pins now are low but e could have been
						//running a little high so cause a delay
						
	lcdLDelay();		//specs says it needs 40ms after Vcc >2.7V
	lcdLDelay();		//but seens to need more
	lcdLDelay();
	
	PTH = 0x38;			//Function Set = 8bit i.f.,2 line,5*7V
	lcdEUp();
	lcdEDown();
	lcdLDelay();		//wait for unclog (>4.1ms)
	
	lcdEUp();
	lcdEDown();
	lcdLDelay();		//wait for unclog (>100us)
	
	lcdEUp();
	lcdEDown();
	lcdLDelay();		//final init sequence
	
	lcdEUp();
	lcdEDown();
	lcdLDelay();		//from spec, shows a 4th itt. of this command
	
	PTH = 0x0C;			//Disp control: Disp On, no cursor, no blink
	lcdEUp();
	lcdEDown();
	lcdLDelay();	
	
	PTH = 0x01;			//Clear Disp
	lcdEUp();
	lcdEDown();
	lcdLDelay();	

	PTH = 0x06;			//Entry Mode Set = inc + no disp shift
	lcdEUp();
	lcdEDown();
	lcdLDelay();		
}

/*-----------------------------------------------------------------
				lcdRWUp
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the R/W* line high (reading)							
--------------------------------------------------------------*/
void lcdRWUp(void)
{
	PORTK |= 0x02;
}

/*-----------------------------------------------------------------
				lcdRWDown
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the R/W* line low (writing)							
--------------------------------------------------------------*/
void lcdRWDown(void)
{
	PORTK &= 0xFD;
}

/*-----------------------------------------------------------------
				lcdEUp
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the E line high (enable LCD)					
--------------------------------------------------------------*/
void lcdEUp(void)
{
	PORTK |= 0x01;
}

/*-----------------------------------------------------------------
				lcdEDown
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the E line low(disable LCD)					
--------------------------------------------------------------*/
void lcdEDown(void)
{
	PORTK &= 0xFE;
}

/*-----------------------------------------------------------------
				lcdRSUp
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the A line high (address 1 (data))					
--------------------------------------------------------------*/
void lcdRSUp(void)
{
	PORTK |= 0x04;
}

/*-----------------------------------------------------------------
				lcdRSDown
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Set the A line low (address 0 (instruction))					
--------------------------------------------------------------*/
void lcdRSDown(void)
{
	PORTK &= 0xFB;
}

/*-----------------------------------------------------------------
				lcdSDelay
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Cause a short delay ~20us				
--------------------------------------------------------------*/
void lcdSDelay(void)
{
	asm ldy #10
	asm  dbne y,*
}

/*-----------------------------------------------------------------
				lcdLDelay
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Cause a long delay ~~49.2ms	by decrementing toascii
				0xFFFF first and then checks for 0
--------------------------------------------------------------*/
void lcdLDelay(void)
{
	asm ldy #0
	asm  dbne y,*
}

/*-----------------------------------------------------------------
				lcdInst
				
Requires:		char 
Returns:		None
Regs Affected:	None
		
Decription:		Send a byte to the instruction reg of LCD on custom
				port - byte comes in as CIn
--------------------------------------------------------------*/
void lcdInst(char cIn)
{
	lcdBusy();		//wait for LCD to not be busy

	PORTK &= ~0x07;		//premark control outputs as low (A=R/W*=E=0)
	
	PTH = cIn;			//Send output to port q
	DDRH = 0xFF;		//set port H as all outputs
	
	lcdSDelay();		//debug
	
	lcdEUp();
	lcdEDown();
}

/*-----------------------------------------------------------------
				lcdData
				
Requires:		char
Returns:		None
Regs Affected:	None
		
Decription:		Send a byte to the LCD at the current cursor location
				--byte comes in as CIn. Use Set_R_C(char,char) to set
				the Row,Col prior to calling this function.
--------------------------------------------------------------*/
void lcdData(char cIn)
{
	lcdBusy();		//wait for LCD to not be busy

	PORTK &= ~0x07;		//premark control outputs as low (A=R/W*=E=0)
	
	PTH = cIn;			//Send output to port q
	DDRH = 0xFF;		//set port H as all outputs
	
	lcdRSUp();			//is data
	lcdEUp();
	lcdEDown();			//latch LCD
}

/*-----------------------------------------------------------------
				lcdBusy
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Wait for lcd to not be bust
--------------------------------------------------------------*/
void lcdBusy(void)
{
	char Lcd_Busy = 0;
	DDRH = 0x00;		//set PortH as inputs
	
	lcdRSDown();		//is instruction
	lcdRWUp();			//reading
	
	do
	{
		lcdSDelay();
		lcdEUp();
		lcdSDelay();		//probably unnecessary
		Lcd_Busy = PTH;  	//status (d7) and address (d6:0)
		Lcd_Busy &= 0x80;
		lcdEDown();
	}
	while(Lcd_Busy != 0);
}

/*-----------------------------------------------------------------
				lcdAddr
				
Requires:		char
Returns:		None
Regs Affected:	None
		
Decription:		Set CG addr in A to LCD
--------------------------------------------------------------*/
void lcdAddr(char cAddress)
{
	lcdBusy();
	cAddress |= 0x80;
	lcdInst(cAddress);
}

/*-----------------------------------------------------------------
				lcdString
				
Requires:		char*
Returns:		None
Regs Affected:	None
		
Decription:		Send a string to the LCD starting at current
				cursor position
--------------------------------------------------------------*/
void lcdString(char* InputString)
{
	char cLetter = '0';
	int iIndex = 0;
	
	while(InputString[iIndex] != '\0' && iIndex < 20)
	{
		cLetter = InputString[iIndex];
		lcdData(cLetter);
		iIndex++;
	}
}

/*-----------------------------------------------------------------
				lcdClear
				
Requires:		None
Returns:		None
Regs Affected:	None
		
Decription:		Clear the display
--------------------------------------------------------------*/
void lcdClear(void)
{
	lcdBusy();
	lcdInst(1);
}

/*-----------------------------------------------------------------
				Set_R_C (Set Cursor at Row/Column)
				
Requires:		cRow contains the row in Zero Based decimal (0-3)
				cCol contains the column in Zero Based decimal (0-19)
Returns:		Calls lcdAddr to set appropirate cursor position
Regs Affected:	None
		
Decription:		This function can be used to convert desired row,column
				cursor position(passed in as cRow and cCol) to LCD Address
				After calculation of LCD address, lcdAddr is called
				to position the cursor.
				
Note: 			If either row or column is not in range, defaults to 0x00
--------------------------------------------------------------*/
void Set_R_C(char cRow, char cCol)
{
	char cAddr = 0;
	
	if(cCol >= 0 && cCol <20)	//check for valid column and then calculate 
								//based on row and col
	{
		switch(cRow)
		{
			case 0:
				cAddr = cCol;
				break;
			case 1:
				cAddr = 0x40 + cCol;
				break;
			case 2:
				cAddr = 0x14 + cCol;
				break;
			case 3:
				cAddr = 0x54 + cCol;
				break;
			default:
				cAddr = 0;
				break;
		}
	}
	lcdAddr(cAddr);
}

/*-----------------------------------------------------------------
				lcdLabels
				
Requires:		4 Strings. (Use "" if no label required)
				Lb0 for Row 0
				Lb1 for Row 1
				Lb2 for Row 2
				Lb3 for Row 3
				
Returns:		Populates  LCD labels
Regs Affected:	None
		
Decription:		Populates all 4 LCDs at once, 1 label a row.
--------------------------------------------------------------*/
void lcdLabels(char* Lb0,char* Lb1,char* Lb2,char* Lb3) 
{
	Set_R_C(0,0);
	lcdString(Lb0);
	Set_R_C(1,0);
	lcdString(Lb1);
	Set_R_C(2,0);
	lcdString(Lb2);
	Set_R_C(3,0);
	lcdString(Lb3);
}