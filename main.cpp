#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"
#include "car.h"




void inputsInit();
void outputsInit();

int main(){
   inputsInit();
   outputsInit();
   while (true){
       engineUpdate();
        displayWrite(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));
        servoUpdate();
        delay(SYSTEM_TIME_INCREMENT_MS);
    }
}

void inputsInit(){
    userInterfaceDisplayInit();
    servoInit();
    carInit();
}