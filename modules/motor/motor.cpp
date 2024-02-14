// Includes
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"
// Defines


// Objects
PwmOut servo(PF_9);

// Function prototypes
void servoInit();
void servoUpdate();


// Initialize the servo
void servoInit() {
    servo.period(PERIOD); // 20ms period
    servo.write(DUTY_MIN);
    delay(2000);
}

// Set the movement of the servo
void servoUpdate() {
    servo.write(DUTY_MAX);
    delay(2000);
    servo.write(DUTY_MIN);
    delay(2000);
}