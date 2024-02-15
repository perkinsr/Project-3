//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declaration of public defines]=========================================
#define DUTY_MIN 0.023
#define DUTY_MAX 0.112
#define PERIOD 0.02

#define SYSTEM_TIME_INCREMENT_MS   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void servoInit();
void servoUpdate();

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_