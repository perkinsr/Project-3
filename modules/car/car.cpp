//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "car.h"

//=====[Defines]===============================================================

//=====[Declaration of public data types]======================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);
DigitalIn driverSeatButton(D10);

DigitalOut engineLed(LED2);


//=====[Declaration and initialization of public global variables]=============


//=====[Declarations (prototypes) of public functions]=========================

//=====[Implementations of public functions]===================================

void carInit()
{
  ignitionButton.mode(PullDown);
  driverSeatButton.mode(PullDown);
  engineLed = OFF;
}


void engineStart() { // Turns the engine on/off based on ignition button and driver sensor
    if (driverSeatButton && ignitionButton){
        int ignitionPressed = 1;
        while (ignitionPressed == 1){
            if (!ignitionButton){
                engineLed = ON;
                ignitionPressed = 0;
            }
        }
    }
}

void engineCheck(){
    if (ignitionButton && engineLed == ON){
        engineLed = OFF;
    }
}
