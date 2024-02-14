//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "potentiometers.h"
#include "display.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn wiperModeSelection(A2);
AnalogIn timeDelay(A3);
//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
float wiperRead = 0.0;
float timeDelayRead = 0.0;
//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void userInterfaceDisplayUpdate(){
    static int accumulatedDisplayTime = 0;
    wiperRead = wiperPotRead();
    timeDelayRead = timePotRead();

    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;
        
        //change all of this to reporesent the read values for the potentiometers
        if (wiperRead < WIPER_INT){
            displayWrite(1,0);
        } else if (wiperRead > WIPER_INT && wiperRead < WIPER_LOW){
            if (timeDelayRead > DELAY_MEDIUM){
                displayWrite(2,1);
            } else if (timeDelayRead > DELAY_MEDIUM && timeDelayRead < DELAY_SHORT){
                displayWrite(2,2);
            } else if (timeDelayRead > DELAY_SHORT){
                displayWrite(2,3);
            }
        } else if (wiperRead > WIPER_LOW && wiperRead < WIPER_HI){
            displayWrite(3,0);
        } else if (wiperRead > WIPER_HI){
            displayWrite(4,0);
        }
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

float wiperPotRead(){
    return wiperModeSelection.read();
}

float timePotRead(){
    return timeDelay.read();
}
//=====[Implementations of private functions]==================================
