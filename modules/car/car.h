//=====[#include guards - begin]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#ifndef _CAR_H_
#define _CAR_H_

//=====[Declaration of public defines]=========================================


//=====[Declaration of public data types]======================================


//=====[Declarations (prototypes) of public functions]=========================

void carInit();

void engineUpdate();
bool engineButtonUpdate();
bool driverSitting();

//=====[#include guards - end]=================================================

#endif // _CAR_H_