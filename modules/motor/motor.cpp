// Includes
#include "mbed.h"
#include "arm_book_lib.h"

// Defines
#define DUTY_MIN 0.023
#define DUTY_MAX 0.112
#define PERIOD 0.02

// Objects
PwmOut servo(PF_9);

// Function prototypes
int main();
void servoInit();
void servoUpdate();

// Main
int main() {
    servoInit();
    while (true) {
    servoUpdate();
    }
}

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