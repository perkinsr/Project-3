#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"
#include "car.h"


void modulesInit();

int main(){
   modulesInit();
    while (true) {
        engineStart();
        engineCheck();
        
        displayWrite(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));
        servoSpeedAndDelay(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));
        delay(SYSTEM_TIME_INCREMENT_MS);
    }
}

void modulesInit(){
    userInterfaceDisplayInit();
    servoInit();
    carInit();
}