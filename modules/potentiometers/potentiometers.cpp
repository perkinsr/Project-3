//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "potentiometers.h"
#include "display.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn wiperModeSelection(A2);
AnalogIn timeDelay(A3);
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

// Function to read the state of the wiper
int readWiperState(float wiperRead) {
    if (wiperRead < WIPER_INT) {
        return WIPER_STATE_INTER;
    } else if (wiperRead > WIPER_INT && wiperRead < WIPER_LOW) {
        return WIPER_STATE_LOW;
    } else if (wiperRead > WIPER_LOW && wiperRead < WIPER_HI) {
        return WIPER_STATE_HI;
    } else { // wiperRead >= WIPER_HI
        return WIPER_STATE_OFF;
    }
}

// Function to read the state of the intermediate mode
int readIntermediateState(float intermediateMode) {
  if (intermediateMode > DELAY_MEDIUM) {
    return INTER_STATE_LONG;
  } else if (intermediateMode > DELAY_SHORT && intermediateMode < DELAY_MEDIUM) {
    return INTER_STATE_MEDIUM;
  } else if (intermediateMode > DELAY_SHORT) {
    return INTER_STATE_SHORT;
  }
  else return -1;
}


/*
void potentiometerCheck(){
    wiperRead = wiperPotRead();
    timeDelayRead = intermediatePotRead(); 
    //change all of this to reporesent the read values for the potentiometers
    if (wiperRead < WIPER_INT){
        displayWrite(1,0);
    } else if (wiperRead > WIPER_INT && wiperRead < WIPER_LOW){
        if (timeDelayRead > DELAY_MEDIUM){
            displayWrite(2,1);
        } else if (timeDelayRead > DELAY_MEDIUM && timeDelayRead < DELAY_SHORT){
            displayWrite(2,2);
        } else if (timeDelayRead > DELAY_SHORT){
            displayWrite(2,3);
        }
    } else if (wiperRead > WIPER_LOW && wiperRead < WIPER_HI){
        displayWrite(3,0);
    } else if (wiperRead > WIPER_HI){
        displayWrite(4,0);
    }
}
*/


float wiperPotRead(){
    return wiperModeSelection.read();
}

float intermediatePotRead(){
    return timeDelay.read();
}
//=====[Implementations of private functions]==================================
