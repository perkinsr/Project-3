// Includes
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"

// Defines
#define DUTY_MIN 0.023
#define DUTY_MAX 0.112
#define PERIOD 0.02
#define INCREMENT 0.01

// Objects
PwmOut servo(PF_9);

// Function prototypes
void servoInit();
void servoUpdate();

// Initialize the servo
void servoInit() {
    servo.period(PERIOD); // 20ms period
}

// Set the movement of the servo
void servoUpdate( int placement) {
    servo.write(DUTY_MAX);
    delay(2000);
    servo.write(DUTY_MIN);
    delay(2000);
}

void servoSlow(){
    float position = DUTY_MIN;
    for (int i = 0; i < 100; i++){
        position = position + INCREMENT;
        servo.write(position);
        delay(50);
    }
}