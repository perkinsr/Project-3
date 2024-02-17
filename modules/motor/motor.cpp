//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "motor.h"
#include "potentiometers.h"
#include "car.h"

//=====[Declaration of private defines]========================================

//position where the motor is at 67 degrees
#define TARGET_POSITION 0.067

//defines values for forward and backward motion
#define FORWARD true
#define BACKWARD false

//values for motor speed increments
#define MOTOR_HIGH 0.003
#define MOTOR_LOW 0.001


//time delays in milliseconds, divided by 2 periods (40ms)
#define TIME_DELAY_SHORT 75
#define TIME_DELAY_MEDIUM 150
#define TIME_DELAY_LONG 200

//=====[Declaration and initialization of public global objects]===============
PwmOut servo(PF_9);

//=====[Declarations (prototypes) of private functions]========================
void servoUpdate(float interval, int timeDelay);
void noTimerServo (float interval);

//=====[Implementations of public functions]===================================

//initializes the servo motor
void servoInit() {
    servo.period(PERIOD); // 20ms period
    servo.write(DUTY_MIN);
    delay(1000);
}


//uses inputs with the wiper states and intermediate delay states and uses them to run the respective
//servo functions with the respective speeds and time delays
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

//=====[Implementations of private functions]==================================

//takes the specific speed and time delay in through the parameters and increments the motor by the given
//ammount in interval every 2 periods (40 milliseconds)
void servoUpdate(float interval, int intermediateTimeDelay){

    //accounts for the motor accumulated timne
    static int accumulatedTime = 0;

    //time delay accumulated time
    static int accumulatedTimeDelay = 0;

    //start position at duty min
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
            engineCheck();
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
            engineCheck();
        }
        accumulatedTime = 0;
    } else {
        accumulatedTime = accumulatedTime + SYSTEM_TIME_INCREMENT_MS;
    } 
    if (cycleComplete == true){
        cycleComplete = false;
    }
}