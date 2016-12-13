/*
; SCI_Lib.inc
;
; Contains:
;	   Rx_Byte
;	   SCI_19200
;	   Tx_Byte
; 	   Tx_String
;
; Author:  YunJie Li
; Date:    April 11, 2016
*/

// Key_hit Function
// Return Value: Routine returns SCI0SR1 & 0x20
// 		 This is checking RDRF
// 		 == 0x20 if a character is waiting
// 		 == 0x00 if no character is in
// 		 Calling program need to look at the return
//		 value and run Rx_Byte if return value is non-zero

unsigned char SCI0_Key_hit(void)
{
  unsigned char ucKey_In = 0;

  ucKey_In = SCI0SR1 & 0x20;

  return ucKey_In;
}

/* 
; Rx_Byte Subroutine
; Returns AccA contains ASCII code for a keyboard press
; This polls the RDRF (Receive Data Register Full Flag)
;   of SCI0SR1 until character is received. The 
;   received character is then stored in A

Rx_Byte:   pshx

	   ldx   #SCI0SR1
bit5clr:   brclr 0,x,#$20,bit5clr
       	   ldaa  SCI0DRL

 	   pulx
 	   rts
*/

unsigned char SCI_RxByte(void)
{
  unsigned char unkey = 0;

  while ((SCI0SR1 & 0x20) == 0);

  return SCI0DRL;
}

/*
; SCI_19200 Subroutine
; Initializes the SCI for 19200, 8N1

SCI_19200: psha
	   pshb

	   ;ldaa #$00		; If write high and low bytes
	   ;staa SCI0BDH 	; separately, the high byte 
	   ;ldaa #26		; must be written first
	   ;staa SCI0BDL
	   
	   ldaa #26		; Set BAUD rate to 19200 
	   std SCI0BD

	   ldaa #$00		; Set 8N1
	   staa SCI0CR1

	   ldaa #$0C		; Enables TX/RX
	   staa SCI0CR2		; SCI interupts off

	   pulb
	   pula

	   rts
*/

// SCI0 Initialization

void SCI0_Init19200(void)
{
  SCI0BDH = 0;
  SCI0BDL = 26;
  SCI0CR1 = 0x00;
  SCICR2 = 0x0C;
}

/*
; Tx_Byte Subroutine
; This routine polls TDRE (transmit data register empty) bit of SCI0SR1 until
;   SCI is ready to transmit. It then sends the data in AccA to SCI data
;   register for transmission (bit7 = 1)

Tx_Byte:   tst SCI0SR1		; Check bit7 of SCI status register
	   bpl Tx_Byte		; if bit7 is 0 then wait, if = 1
	   staa SCI0DRL		; write data into data register
	   rts			; for transmission
*/

void SCI0_TxByte(unsigned char cVal)
{
  while ((SCI0SR1 & 0x80) == 0) { }	// Wait until transmit register
    					// is empty prior to sending
					
  SCI0DRL = cVal;			// Write the character to the 
					// transmit register

/*
; Tx_String Subroutine
; This routine expects the starting address of the string to be in x.
;   It calls Tx_Byte to transmit each element of the string. It also checks for 
;   end of string character 00 (null) at which time is drops thru to rts

Tx_String: psha
	   pshx

tx_again:  ldaa 0,x		; Load contents of character to
	   beq tx_done		; send into AccA, if contents are
				; 00 (a null) then branch to end
	   inx			; point to next character
	   jst Tx_Byte		; Transmit data byte to SCI data register
	   bra tx_again		; Do another byte

tx_done:   pulx
	   pula
	   rts
*/

void SCI0_TxString(char * cString)	// Pointer to chars
{
  while (*cString != 0)
  {
    SCI0_TxByte(*cString++);
  }
}

