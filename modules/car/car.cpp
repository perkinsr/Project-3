//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "car.h"

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);
DigitalIn driverSeatButton(D10);

DigitalOut engineLed(LED2);


//=====[Implementations of public functions]===================================

//initializes all of the buttons and LEDs
void carInit()
{
  ignitionButton.mode(PullDown);
  driverSeatButton.mode(PullDown);
  engineLed = OFF;
}

// checks to see if the ignition can be started
void engineStart() { 
    //if the driver is seated and the button is pressed, turn the blue LED on when the 
    //ignition button is released
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

//check to see if the ignitionButton to turn off the engine
void engineCheck(){
    if (ignitionButton && engineLed == ON){
        engineLed = OFF;
    }
}

//check the state of the engineLed to see if the engine is on or not
bool getLedState(){
    return engineLed;
}
