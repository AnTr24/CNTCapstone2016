#include "derivative.h"
#include "LCD_4Line_C.h"

void lcdRWUp(void) {  
  PORTK |= 0x02;
}

void lcdRWDown(void) {  
  PORTK &= 0xFD;
}

void lcdEUp(void) {
  PORTK |= 0x01; 
}

void lcdEDown(void) {
  PORTK &= 0xFE;
}

void lcdRSUp(void) {
  PORTK |= 0x04;
}

void lcdRSDown(void) {
  PORTK &= 0xFB;
}

void lcdSDelay(void) {
  asm ldy #10
  asm dbne y,*
}

void lcdLDelay(void) {
  asm ldy #0
  asm dbne y,*
}

void lcdInit(void) {
  PTH = 0x00;
  DDRH = 0xFF;
  
  PORTK &= ~0x07;
  DDRK |= 0x07;
  
  lcdLDelay();
  lcdLDelay();
  lcdLDelay();
  
  PTH = 0x38;
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  PTH = 0x0C;
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  PTH = 0x01;
  lcdEUp();
  lcdEDown();
  lcdLDelay();
  
  PTH = 0x06;
  lcdEUp();
  lcdEDown();
  lcdLDelay();
}

void lcdInst(char cIn) {
  lcdBusy();
  
  PORTK &= ~0x07;
  
  PTH = cIn;
  DDRH = 0xFF;
  
  lcdSDelay();
  
  lcdEUp();
  lcdEDown();
}

void lcdData(char cIn) {
  lcdBusy();
  
  PORTK &= ~0x07;
  
  PTH = cIn;
  DDRH = 0xFF;
  
  lcdRSUp();
  lcdEUp();
  lcdEDown();
}

void lcdBusy(void) {
  char Lcd_Busy = 0;
  DDRH = 0x00;
  
  lcdRSDown();
  lcdRWUp();
  
  do {
    lcdSDelay();
    lcdEUp();
    lcdSDelay();
    Lcd_Busy = PTH;
    Lcd_Busy &= 0x80;
    lcdEDown();
  }
  while (Lcd_Busy != 0);
}

void lcdAddr(char cAddress) {
  lcdBusy();
  cAddress |= 0x80;
  lcdInst(cAddress);
}

void lcdCGAddr(char cAddress) {
  lcdBusy();
  cAddress &= 0x3F;
  cAddress |= 0x40;
  lcdInst(cAddress);
}

void lcdString(char* InputString) {
  char cLetter = '0';
  int iIndex = 0;
  
  while (InputString[iIndex] != '\0' && iIndex < 20) {
    cLetter = InputString[iIndex];
    lcdData(cLetter);
    iIndex++;
  }
}

void lcdClear(void) {
  lcdBusy();
  lcdInst(1);
}

void Set_R_C(char cRow, char cCol) {
  char cAddr = 0;
  
  if (cCol >= 0 && cCol < 20) {
    switch(cRow) {
      case 0:
      cAddr = cCol;
      lcdAddr(cAddr);
      break;
      
      case 1:
      cAddr = 0x40 + cCol;
      lcdAddr(cAddr);
      break;
      
      case 2:
      cAddr = 0x14 + cCol;
      lcdAddr(cAddr);
      break;
      
      case 3:
      cAddr = 0x54 + cCol;
      lcdAddr(cAddr);
      break;
  
      default:
      cAddr = 0;
      lcdAddr(cAddr);
      break;
    }
  } else {
    lcdAddr(cAddr);
  }
}

void lcdLabels(char* Lb0, char* Lb1, char* Lb2, char* Lb3) {
  Set_R_C(0, 0);
  lcdString(Lb0);
  Set_R_C(1, 0);
  lcdString(Lb1);
  Set_R_C(2, 0);
  lcdString(Lb2);
  Set_R_C(3, 0);
  lcdString(Lb3);
}
  