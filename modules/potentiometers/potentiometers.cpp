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
        return WIPER_STATE_OFF;
    } else if (wiperRead > WIPER_INT && wiperRead < WIPER_LOW) {
        return WIPER_STATE_INTER;
    } else if (wiperRead > WIPER_LOW && wiperRead < WIPER_HI) {
        return WIPER_STATE_LOW;
    } else { 
        return WIPER_STATE_HI;
    }
}

// Function to read the state of the intermediate mode
int readIntermediateState( float intermediateMode) {

    if (intermediateMode < DELAY_MEDIUM) {
    return INTER_STATE_LONG;
    } else if (intermediateMode < DELAY_SHORT && intermediateMode > DELAY_MEDIUM) {
    return INTER_STATE_MEDIUM;
    } else if (intermediateMode > DELAY_SHORT) {
    return INTER_STATE_SHORT;
    } else {
    return INTER_STATE_SHORT;
    }
}



//=====[Implementations of private functions]==================================
float wiperPotRead(){
    return wiperModeSelection.read();
}

float intermediatePotRead(){
    return timeDelay.read();
}