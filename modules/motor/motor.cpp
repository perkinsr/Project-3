// Includes
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"
// Defines
#define SET_TIME_INTERVAL 40
#define INCREMENT 0.01
#define TARGET_POSITION 0.03312778

#define FORWARD true
#define BACKWARD false

// Objects
PwmOut servo(PF_9);

// Function prototypes
void servoInit();
void servoUpdate();
void servoSlow();
float servoDegreesToPosition(float degrees);


// Initialize the servo
void servoInit() {
    servo.period(PERIOD); // 20ms period
    servo.write(DUTY_MIN);
    delay(1000);
}

// Set the movement of the servo
void servoUpdate() {
    servo.write(DUTY_MAX);
    delay(2000);
    servo.write(DUTY_MIN);
    delay(2000);
}





float servoDegreesToPosition(float degrees) {
    if (degrees<180 && degrees >0) {
        return degrees*(DUTY_MAX-DUTY_MIN)/180;
    }
    else {
        return DUTY_MIN;
    }
}

void servoWipersUpdate(float wiperState) {
    static int accumulatedTime;
    if (accumulatedTime>=SET_TIME_INTERVAL){}

}

void servoWipersTest() {

}

void servoSpeed(int wiperState){
    static int accumulatedTime = 0;
    static float position = DUTY_MIN;
    if (accumulatedTime >= 40){
        accumulatedTime = 0;
        position = position + wiperState;
        servo.write(position);
        delay(50);
    } else if (){

    }

    accumulatedTime = accumulatedTime + SYSTEM_TIME_INCREMENT_MS;
}