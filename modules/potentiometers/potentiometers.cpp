//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "potentiometers.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn wiperModeSelection(A1);
AnalogIn timeDelay(A2);
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
float wiperPotRead(){
    return wiperModeSelection.read();
}

float timePotRead(){
    return timeDelay.read();
}
//=====[Implementations of private functions]==================================
