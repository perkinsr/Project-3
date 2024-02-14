//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "serial_com.h"
#include "display.h"
#include "potentiometers.h"
#include "motor.h"


//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
UnbufferedSerial uartUsb(USBTX, USBRX, 115200);
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
float wiperRead = 0.0;
float timeDelayRead = 0.0;
//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================




//=====[Implementations of private functions]==================================
