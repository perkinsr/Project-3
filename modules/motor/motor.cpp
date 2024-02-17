// Includes
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"
#include "potentiometers.h"

// Defines
#define SET_TIME_INTERVAL 40
#define TARGET_POSITION 0.067

#define FORWARD true
#define BACKWARD false

#define MOTOR_HIGH 0.01
#define MOTOR_LOW 0.003

#define TIME_DELAY_SHORT 75
#define TIME_DELAY_MEDIUM 150
#define TIME_DELAY_LONG 200

// Objects
PwmOut servo(PF_9);

// Function prototypes
void servoUpdate(float interval, int timeDelay);
void noTimerServo (float interval);
// Initialize the servo
void servoInit() {
    servo.period(PERIOD); // 20ms period
    servo.write(DUTY_MIN);
    delay(1000);
}

void servoSpeedAndDelay(int wiperState, int intermediateState){
    if (wiperState == WIPER_STATE_INTER){
        if (intermediateState == INTER_STATE_SHORT){
            servoUpdate(MOTOR_LOW, TIME_DELAY_SHORT);
        } else if (intermediateState == INTER_STATE_MEDIUM){
            servoUpdate(MOTOR_LOW, TIME_DELAY_MEDIUM);
        } else if (intermediateState == INTER_STATE_LONG){
            servoUpdate(MOTOR_LOW, TIME_DELAY_LONG);
        }
    } else if (wiperState == WIPER_STATE_LOW){
        noTimerServo(MOTOR_LOW);
    } else if (wiperState == WIPER_STATE_HI){
        noTimerServo(MOTOR_HIGH);
    }
}

void servoUpdate(float interval, int intermediateTimeDelay){
    static int accumulatedTime = 0;
    static int accumulatedTimeDelay = 0;
    static float position = DUTY_MIN;
    static bool direction = FORWARD;
    static bool cycleComplete = false;

    if (accumulatedTime >= 4){

        while (cycleComplete == false){
            if (position >= TARGET_POSITION){
                direction = BACKWARD;
            } 
            if (direction == BACKWARD && position >= DUTY_MIN){
                position = position - interval;
                servo.write(position);
                delay(40);
            } 
            if (position < DUTY_MIN){
                direction = FORWARD;
                cycleComplete = true;
            }
            if (direction == FORWARD && position <= TARGET_POSITION){
                position = position + interval;
                servo.write(position);
                delay(40);
            }
        } 
        if (cycleComplete == true && accumulatedTimeDelay != intermediateTimeDelay){
            accumulatedTimeDelay++;
        } else if (accumulatedTimeDelay == intermediateTimeDelay){
            cycleComplete = false;
            accumulatedTimeDelay = 0;
        }
        
        accumulatedTime = 0;
    } else {
        accumulatedTime = accumulatedTime + SYSTEM_TIME_INCREMENT_MS;
    } 

}

void noTimerServo (float interval){
    static int accumulatedTime = 0;
    static int accumulatedTimeDelay = 0;
    static float position = DUTY_MIN;
    static bool direction = FORWARD;
    static bool cycleComplete = false;

    if (accumulatedTime >= 4){

        while (cycleComplete == false){
            if (position >= TARGET_POSITION){
                direction = BACKWARD;
            } 
            if (direction == BACKWARD && position >= DUTY_MIN){
                position = position - interval;
                servo.write(position);
                delay(40);
            } 
            if (position < DUTY_MIN){
                direction = FORWARD;
                cycleComplete = true;
            }
            if (direction == FORWARD && position <= TARGET_POSITION){
                position = position + interval;
                servo.write(position);
                delay(40);
            }
        }
        accumulatedTime = 0;
    } else {
        accumulatedTime = accumulatedTime + SYSTEM_TIME_INCREMENT_MS;
    } 
    if (cycleComplete == true){
        cycleComplete = false;
    }
}