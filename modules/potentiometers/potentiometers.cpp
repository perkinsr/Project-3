//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "potentiometers.h"
#include "display.h"

//=====[Declaration and initialization of public global objects]===============

AnalogIn wiperModeSelection(A2);
AnalogIn timeDelay(A3);

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

//returns the value of the wiperModeSelection potentiometer
float wiperPotRead(){
    return wiperModeSelection.read();
}

//returns the value of the timeDelay potentiometer
float intermediatePotRead(){
    return timeDelay.read();
}