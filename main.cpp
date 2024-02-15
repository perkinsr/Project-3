#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"
#include "car.h"

#define SYSTEM_TIME_INCREMENT_MS   10


void modulesInit();

int main(){
   modulesInit();
   while (true){
       engineUpdate();
        displayWrite(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));
        servoUpdate();
        delay(SYSTEM_TIME_INCREMENT_MS);
    }
}

void modulesInit(){
    userInterfaceDisplayInit();
    servoInit();
    carInit();
}