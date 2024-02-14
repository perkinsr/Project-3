// Includes
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"
// Defines
#define SET_TIME_INTERVAL 40

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

}

void servoSlow(){
    float position = DUTY_MIN;
    for (int i = 0; i < 100; i++){
        position = position + INCREMENT;
        servo.write(position);
        delay(50);
    }
}

float servoDegreesToPosition(float degrees) {
    if (degrees<180 && degrees >0) {
        return degrees*(DUTY_MAX-DUTY_MIN)/180;
    }
    else {
        return DUTY_MIN;
    }
}

void servoWipersUpdate(int mode) {
    static int accumulatedTime;
    if (accumulatedTime>=SET_TIME_INTERVAL)
        if (mode == OFF) {
        }
        if (mode == HIGH) {
        }
        if (mode == LOW) {
        }
}