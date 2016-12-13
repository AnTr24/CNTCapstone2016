#include "derivative.h"
#include "Delay_C.h"
#include "A2D_Lib_C.h"

// ATD0_Init
void ATD0_Init(void) {
  ATD0CTL2 = 0xE0;
  
  ATD0CTL3 = 0x0A;
  ATD0CTL4 = 0x26;
  Delay_C(100);
}

// ATD0_Sample0
unsigned int ATD0_Sample0(void) {
  unsigned int uiResult = 0;
  
  ATD0CTL5 = 0x80;
  
  while ((ATD0STAT0 & 0x80) == 0);
  
  uiResult = ATD0DR0;
  
  return uiResult;
}