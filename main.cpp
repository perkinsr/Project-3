#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"
//#include "serial_com.h"
#include "motor.h"

#define DUTY_MIN 0.02
#define DUTY_MAX 0.20
#define PERIOD 0.02

DigitalIn driverSeat(D10);
DigitalIn ignitionButton(BUTTON1);

DigitalOut engineLED(LED2);



void inputsInit();
void outputsInit();

int main(){
   inputsInit();
   outputsInit();
   int driverSeatState = 0;
   int engineState = 0;
   while (true){
        //userInterfaceDisplayUpdate();
        //serialComPrint();
        servoSlow();
    }
}

void inputsInit(){
    driverSeat.mode(PullDown);
    ignitionButton.mode(PullDown);
    userInterfaceDisplayInit();
}

void outputsInit(){
    engineLED = OFF;
    servo.period(PERIOD);
}