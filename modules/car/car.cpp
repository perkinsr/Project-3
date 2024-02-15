//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "car.h"

//=====[Defines]===============================================================

//=====[Declaration of public data types]======================================

typedef enum { //Object that implements our state table for the ignition button
  WAIT,
  BUTTON_PRESSED,
  BUTTON_RELEASED
} ignitionButtonState_t;

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);
DigitalIn driverSeatButton(D2);

DigitalOut engineLed(LED2);

ignitionButtonState_t ignitionButtonState;

//=====[Declaration and initialization of public global variables]=============


//=====[Declarations (prototypes) of public functions]=========================

//=====[Implementations of public functions]===================================

void carInit()
{
  ignitionButton.mode(PullDown);
  driverSeatButton.mode(PullDown);
  ignitionButtonState = WAIT;
  engineLed = OFF;
}


void engineUpdate() { // Turns the engine on/off based on ignition button and driver sensor
 if (engineButtonUpdate()) {
     if (!engineLed) {
         if (driverSitting()) {
             engineLed = ON;
         }
     }
     else {
         engineLed = OFF;
     }
 }
}

bool engineButtonUpdate(){ // Implements the state table for the ignition button
  switch(ignitionButtonState){
      case WAIT :
          if(ignitionButton){
              ignitionButtonState = BUTTON_PRESSED;
          }
      break;
      case BUTTON_PRESSED :
          if(!ignitionButton){
              ignitionButtonState = BUTTON_RELEASED;
          }
      break;
      case BUTTON_RELEASED :
          ignitionButtonState = WAIT;
          return true;
      break;
  }
  return false;
}

bool driverSitting(){
if(driverSeatButton){
  return true;
}
  return false;
}