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


//guess and checked values for 3, 6, and 8 second delays respectively
#define TIME_DELAY_SHORT 20
#define TIME_DELAY_MEDIUM 40
#define TIME_DELAY_LONG 55

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
//ammount in interval every 2 periods (40 milliseconds). This is only used for the interval setting
void servoUpdate(float interval, int intermediateTimeDelay){

    //accounts for the motor accumulated timne
    static int accumulatedTime = 0;

    //time delay accumulated time
    static int accumulatedTimeDelay = 0;

    //start position at duty min
    static float position = DUTY_MIN;
    static bool direction = FORWARD;
    static bool cycleComplete = false;

    //if it has been 40 milliseconds, run the following while loop
    if (accumulatedTime >= 40){
        
        //this while loop ensures that the speed or time delay can't be changed in the middle of a cycle
        while (cycleComplete == false){

            //if the position is equal to or greater than 67 degrees from the duty min, change the direction
            //to backwards
            if (position >= TARGET_POSITION){
                direction = BACKWARD;
            } 

            //move backwards until duty min is reached
            if (direction == BACKWARD && position >= DUTY_MIN){
                position = position - interval;
                servo.write(position);
                //makes sure the servo is only moving once every two periods during this while loop
                delay(40);
            } 

            //if the position is less than duty min, move forward again and set cycleComplete to true
            //indicating that a cycle has been completed and the time delay and speed can be changed
            if (position < DUTY_MIN){
                direction = FORWARD;
                cycleComplete = true;
            }

            //move forward until 67 degrees is reaches
            if (direction == FORWARD && position <= TARGET_POSITION){
                position = position + interval;
                servo.write(position);
                //makes sure the servo is only moving once every two periods during this while loop
                delay(40);
            }
            //check to see if the ignitionButton is pressed during this process
            engineCheck();
        } 

        //once a revolution is compete, increment accumulatedTimeDelay ever 40 milliseconds until it has
        //reached the specified time delay
        if (cycleComplete == true && accumulatedTimeDelay != intermediateTimeDelay){
            accumulatedTimeDelay++;

        //once the specified time delay is reached, a new cycle can start and set the accumulatedTimeDelay
        // to zero
        } else if (accumulatedTimeDelay == intermediateTimeDelay){
            cycleComplete = false;
            accumulatedTimeDelay = 0;
        }
        
        accumulatedTime = 0;
    
    //if it hasn't been 40 milliseconds, increment accumulatedTime by the given system time delay
    } else {
        accumulatedTime = accumulatedTime + SYSTEM_TIME_INCREMENT_MS;
    } 

}

//does the same motor process as in servoUpdate except there is no time delay accounted for. This is only 
//used for LOW and HI speeds
void noTimerServo (float interval){
    static int accumulatedTime = 0;
    static int accumulatedTimeDelay = 0;
    static float position = DUTY_MIN;
    static bool direction = FORWARD;
    static bool cycleComplete = false;

    if (accumulatedTime >= 40){

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