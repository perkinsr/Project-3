#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"


DigitalIn driverSeat(D10);
DigitalIn ignitionButton(BUTTON1);

DigitalOut engineLED(LED2);



void inputsInit();
void outputsInit();

int main(){
   inputsInit();
   outputsInit();
   int engineState = 0;
   while (true){
       if (ignitionButton && driverSeat){
           engineLED = ON;
           engineState = 1;
       }
   }
   while (engineState == 1){
        displayWrite(readWiperState(wiperPotRead()), readIntermediateState(intermediatePotRead()));
        servoUpdate();
        delay(SYSTEM_TIME_INCREMENT_MS);
    }
}

void inputsInit(){
    driverSeat.mode(PullDown);
    ignitionButton.mode(PullDown);
    userInterfaceDisplayInit();
    servoInit();
}

void outputsInit(){
    engineLED = OFF;
}