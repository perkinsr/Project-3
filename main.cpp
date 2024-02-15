#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"
#include "car.h"


void modulesInit();

int main(){
   modulesInit();
   while (true){
       if (TIME_RUNNING >= TIME_DELAY){

       }
       
       engineUpdate();
       float wiperPotReading = wiperPotRead();
       float intermediatePotReading = intermediatePotRead();
       int wiperState = readWiperState(wiperPotReading);
       int intermediateState = readIntermediateState(intermediatePotReading);
        displayWrite(wiperState, intermediateState);
        servoUpdate();
        delay(SYSTEM_TIME_INCREMENT_MS);
    }
}

void modulesInit(){
    userInterfaceDisplayInit();
    servoInit();
    carInit();
}