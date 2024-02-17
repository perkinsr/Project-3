//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"
#include "car.h"

//=====[Initialization of public functions]=====================================
void modulesInit();

//=====[Main Function]===========================================================
int main(){
   modulesInit();
   while (true){
       //don't start the running the motor and display until the engineLed is on, indicating that the engine is //turned on correctly
        while (getLedState() == OFF){
            engineStart();
        }
        while (getLedState() == ON) {
            //check to see if the ingition is turned off
            engineCheck();
            
            //update the display
            displayWrite(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));

            //update the motor
            servoSpeedAndDelay(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));

            //delay 10ms after each iteration
            delay(SYSTEM_TIME_INCREMENT_MS);
        }
    }
}

//=====[Implementations of public functions]===================================

//initialize the display, servo motor, and car systems
void modulesInit(){
    userInterfaceDisplayInit();
    servoInit();
    carInit();
}