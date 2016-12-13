/********************************************************************/
// HC12 Program:	ReactionTester - Tests Reaction Times
// Processor:		MC9S12XDP512
// Xtal Speed:		16 MHz
// Author:			YunJie Li, Andy Tran
// Date:			Oct 2016

// Details: Tests a person's reaction time, averaging it voer 3 tests
//          Afterwards, sends data to PC for processing.
/********************************************************************/
//		Library includes
/********************************************************************/

#include <hidef.h>          /* common defines and macros */
#include "derivative.h"     /* derivative-specific definitions */
#include "Delay_C.h"        //Delay function library, freezes micro
#include "LCD_4Line_C.h"    //LCD, displays text 
#include "RYG_LEDs_C.h"     //RYG LEDs , turn lights on/off
#include "Switches_C.h"     //PT1AD1 switches library
#include "SevSeg_C.h"       //Seven Segment LEDs, debugging
#include "SCI_LIB_C.h"      //For serial communications
#include "stdio.h"          //For sprintf    
#include "stdlib.h"         //For rand function


/********************************************************************/
//		Prototypes
/********************************************************************/
void StartTimer(void);                    //Function to initialzie the timer
unsigned char Switch_Check(void);         //Checks switch states
void SCI0_SendData(unsigned char, float); //Writes a label text and then data to serial port
void ShowInstructionPrompt(void);         //Displays starting instructions
void ShowReadyPrompt(void);               //Displays additional instructions
void ShowNewTestPrompt(void);             //Introductory prompt for start of new tests
void ShowTestVariables(void);             //Debugging function: Dispalys some test variables on lcd

/********************************************************************/
//		Variables
/********************************************************************/
unsigned int randTim;         //Holds the rand() value
unsigned int randLightOn;     //Determines the length of "stanby" phase

unsigned int timeStart;       //Start value of reaction timer
unsigned int timeStop;        //Stop value of reaction timer
unsigned int TOFCount = 0;    //Counter for timer overflow flags

unsigned char tests = 0;      //Current Test Counter
unsigned char tTests = 3;     //Total number of tests to average
float rTime;                  //The user's current reaction time
float rTimeT1 = 0;            //Test 1 result
float rTimeT2 = 0;            //Test 2 result
float rTimeT3 = 0;            //Test 3 result
float average =0;             //Average reaction time.
float rTimeOut = 9.99;        //Max time for each test

char s[20];                   //Array to hold sprintf output
unsigned char sw_state = 0;   //byte to hold switch states
unsigned char btnPressed = 0;        //Flag for button/PortJ interrupt
unsigned char testStart = 0;  //Flag for reaction test start

char newLine[4] = "\r\n";     //Outputing a newline to SerialPort 

//Labels for the data sent to serial port:  
//Test markers
unsigned char cStartMarker = 0x7E;  //start marker to send for data validation   0x7E = '~'
unsigned char cEndMarker = 0x21;    //end marker to send for data validation 0x21 = '!'
/*  
char strT1[10] = "Test 1:";   
char strT2[10] = "Test 2:";
char strT3[10] = "Test 3:";
char strAvg[10] = "Average:";   
*/

/********************************************************************/
//		Lookups
/********************************************************************/


void main(void)
{
// main entry point
_DISABLE_COP();

/********************************************************************/
// initializations
/********************************************************************/

  led_sw_init();
  lcdInit();
  SevSegInit();
  Sw_Init();
  lcdInit();
  SCI_19200();
  
  /* put your own code here */
  StartTimer();         //Enable timer
  
  //Setting up PortJ for button press interrupts
  DDRJ &= 0b11111110;   //set PortJ0 for input 
  PPSJ |= 0b00000001;   //trigger on rising edge
  PIEJ |= 0b00000001;   //enable PortJ0 for interrupt
  PIFJ |= 0b00000001;   //clear interrupt flag  
  EnableInterrupts;
  
  //Display starting prompt
  ShowNewTestPrompt();
  
  //main program loop
  for(;;) {
  
   //run the test multiple times to get an average
    do{
        //Wait till button is pressed to start.
        testStart = Switch_Check();
        
        //Is user ready/button pressed?
        if(testStart) {
        //Ready, so start test
        
        Red_On();//Red LED indicates user should get ready to press button 

        //Display instructions
        if(tests == 0) {
          ShowInstructionPrompt();
          Delay_C(8000);
        }
        
        //starting!
        lcdClear();
        Set_R_C(2,5);
        lcdString("Starting!");
        
        
        //Randomize the stanby time till the green LED turns on
        srand(TCNT);        //seed for random generator is current timer pointer
        randTim = rand();   //Get a random value between 0 and RAND_MAX(  
        randLightOn = randTim % 2000 + 4000; //randomize between 4-6 seconds stanby
        
        //for testing purpose, display stanby time 
        /*
        Set_R_C(3,0);
        lcdString("Delay(ms):");
        Set_R_C(3,11);
        if(sprintf(s,"%8u",randLightOn)>=0)
            lcdString(s);
        */
        
        Delay_C(randLightOn); //wait for stanby value
        
        Green_On(); //Green light starts the input capturing

        timeStart = TCNT; //grab starting timer value 
        TOFCount = 0;     //reset timer overflow counter to 0
        
        while(!btnPressed)     //Wait till interrupt is caused by button
            asm WAI;  
        //At this point, reaction time has been captured
        
        average += rTime; //add to total
        tests++;          //1 test done, time for next
        
        //Display current result
        lcdClear();
        Set_R_C(0,3);
        lcdString("Reaction Time");
        Set_R_C(2,7);
        if(sprintf(s,"%5.3f",rTime)>=0)
              lcdString(s);
                
        Delay_C(3000); //delay till next test 
        
        //reset test starting variables
        btnPressed =0;
        testStart = 0x00;
        
        //Show how many tests user has left to take
        lcdClear();
        Set_R_C(1,0);
        lcdString("Tests left:");
        Set_R_C(1,11);
        if(sprintf(s,"%8u",(tTests - tests))>=0)
          lcdString(s);
        Delay_C(2000);  //display for 5 seconds
        
        ShowReadyPrompt();  //Re-display Wait message
      }
        
    }while(tests < tTests);   //loop till 3 tests have been taken
                                   
    
    average /= tTests; //now average out total
    
    //Display average
    lcdClear();
    Set_R_C(0,4);
    lcdString("Average Time");
    Set_R_C(2,7);
    if(sprintf(s,"%-5.3f",average)>=0)
      lcdString(s);
    
     
    //Check if all times are valid, then send
    if(rTimeT1 <= rTimeOut && rTimeT2<= rTimeOut && rTimeT3 <= rTimeOut) 
    { 
      //***Send Data to PC***
      //Send Starting marker
      Tx_Byte(cStartMarker);
      //Sending test 1
      if(sprintf(s,"%-1.3f",rTimeT1)>=0)
        Tx_String(s);
      //Sending test 2
      if(sprintf(s,"%-1.3f",rTimeT2)>=0)
        Tx_String(s);
      //Sending test 3  
      if(sprintf(s,"%-1.3f",rTimeT3)>=0)
        Tx_String(s);
      //Send End marker
      Tx_Byte(cEndMarker);
      //***Send Complete***
    }

    //reset test values
    tests = 0;       
    average = 0;
    rTimeT1 = 0;
    rTimeT2 = 0;
    rTimeT3 = 0; 
    
    Delay_C(15000); //delay till next test
    
    //Re-display starting prompt
    ShowNewTestPrompt();
  }
}
/********************************************************************/
//		Functions
/********************************************************************/

//Function: StartTimer
//Arg:      None
//Return:   None
//Description:  This function will start the timer and
//              the timer channel 0 for interrupts 
void StartTimer(void) {
  TSCR1 = 0b10000000;     //Turn timer on
  TSCR2 &= 0b11111000;    //clear prescaler bits   
  TSCR2 |= 0b00000110;    //set prescaler  x64
  TIOS |= 0b00000001;     //TIOS0 set to output compare
  TCTL2 &= 0b11111100;    //Cleairng bits for output to PT0
  TCTL2 |= 0b00000001;    //Set low bit for TC0 for toggle(01) on PT0
  TIE |= 0b00000001;      //enable channel 0 for interrupts
  TFLG1 = 0b00000001;     //clear TC0 flag
  TFLG2 |= 0b10000000;     //clear TOF flag
  TC0 = 0;                //set interval 
}

//Function: Switch_Check
//Arg:      None
//Return:   unsigned char - State of the switch presses
//Description:  This function will check the state of the switches
//              and return their value
//Top Switch on:      0x10
//Left Switch on:     0x08
//Right Switch on:    0x02
//Center Switch on:   0x01
//Botton Switch on:   0x04             
unsigned char Switch_Check(void)
{
    unsigned char Sw_states = Get_Switches();
    
    if(Sw_states)					    //optional: wait for switches up				
	    Wait_for_Switches_up();         //before running switch actions
	  
	  return Sw_states;   
}

//Function: SCI0_SendData
//Arg:      unsigned char cMarker - Marker to send
//Arg:      float fData -   Data to be sent as a float
//Return:   None
//Description:  This function will write to the SerialPort a label and data value.
//              Ex: (clabel)  (fData)
//                  Test1:    0.0132
void SCI0_SendData(unsigned char cMarker, float fData) 
{
    //Writes marker to SerialPort
   Tx_Byte(cMarker);
   
   //Converts fData to a set of characters, then sends them one at a time 
    if(sprintf(s,"%-5.3f",fData)>=0)
      Tx_String(s);
    Tx_String(newLine);
}
  
//Function: ShowInstructionPrompt
//Arg:      None
//Return:   None
//Description:  Clears LCD, and shows starting
//              instructions to the user.
void ShowInstructionPrompt(void) {
  lcdClear();
  Set_R_C(0,0);
  lcdString("Reaction Time Tester");
  Set_R_C(2,0);
  lcdString("Hit the button when");
  Set_R_C(3,0);
  lcdString("GREEN light is ON!");    
}

//Function: ShowReadyPrompt
//Arg:      None
//Return:   None
//Description:  Clears LCD, prompts user to start test
//              when ready
void ShowReadyPrompt(void) {
  lcdClear();
  Set_R_C(2,0);
  lcdString("When ready:");
  Set_R_C(3,0);
  lcdString("Press the button.");  
}

//Function: ShowNewTestPrompt
//Arg:      None
//Return:   None
//Description:  Clears LCD, prompts user to start test
//              when ready
void ShowNewTestPrompt(void) {
  lcdClear();
  Set_R_C(0,0);
  lcdString("Reaction Time Tester");
  Set_R_C(2,0);
  lcdString("To get started:");
  Set_R_C(3,0);
  lcdString("Press the button.");  
}

//Function: ShowTestVariables
//Arg:      None
//Return:   None
//Description:  Debugging function to show some variables to LCD
void ShowTestVariables(void) {
  lcdClear();
  Set_R_C(0,0);
  lcdString("Reaction T:");
  Set_R_C(0,11);
  if(sprintf(s,"%5.3f",rTime)>=0)
        lcdString(s);

  Set_R_C(1,0);
  lcdString("Start:");
  Set_R_C(1,11);
  if(sprintf(s,"%5u",timeStart)>=0)
        lcdString(s);

  Set_R_C(2,0);
  lcdString("Stop:");
  Set_R_C(2,11);
  if(sprintf(s,"%5u",timeStop)>=0)
        lcdString(s);

  Set_R_C(3,0);
  lcdString("FlagCount:");
  Set_R_C(3,11);
  if(sprintf(s,"%5u",TOFCount)>=0)
        lcdString(s);
}
/********************************************************************/
//		Interrupt Service Routines
/********************************************************************/
//Interrupt for PORTJ0 
//Desciption: Triggers an interrupt when a button conencted to PortJ is pressed
//            If the green LED is on, will capture the response time of the user       
interrupt VectorNumber_Vportj void SwitchISR(void) 
{
    unsigned char GreenState = PT1AD1 & 0x20; //Grab state of green LED
    
    PIFJ |= 0b00000001;   //acknowledge interrupt
    
    //Green LED ON so input can now be captured
    if(GreenState == 0x20) {
      Green_Off();      //Turn green led off
      Red_Off();        //and red
      timeStop = TCNT;  //Grab the button press timing  
      btnPressed = 1;          //enable flag for test completion
      
      //this is the calculation for converting
      //the timer value/character counts into real time
      //Grabs the total character counts passed since timer start,
      //accounting for the overflows in the timer counter.
      //(Timer goes from 0->65535 or 0x0000 -> 0xFFFF and then overflows)
      //Then the character count is converted into time.
      //Assuming prescaler is x68: 1 character = 8ms
      //Formula: 
      //Reaction Time =(T2 + FlagCount*MaxTimerChracters - T1) * CharacterToTimeRatio
      rTime = (timeStop+TOFCount*65536-timeStart)*0.000008;
      
      //Save test results
      if(tests == 0) 
      {//first test
        rTimeT1 = rTime;
      }
      if(tests == 1) 
      { //second test
        rTimeT2 = rTime;
      }
        
      if(tests == 2) 
      { //third test
        rTimeT3 = rTime;
      }
      
      //For debugging purposes
      //Display test variables to LCD
      //ShowTestVariables();
      
    }
    
}

//Interrupt for timer channel 0
//Description:  periodically checks the timer to see if
//              and overflow occured. A running counter
//              will track the overflows counts 
//              for response time calculations
interrupt VectorNumber_Vtimch0 void TimerInterval(void) 
{                                          
    TFLG1 = 0b00000001;  //acknowledge interrupt
    
    //check if timer overflow occured
    if((TFLG2 & 0b10000000) == 0b10000000)   //Checks the TOF flag in the TFLG2 register
    {
        TOFCount++;           //add to overflow counter
        TFLG2 |= 0b10000000;  //clear TOF/overflow flag     
    }
     
}

