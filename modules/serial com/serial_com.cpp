//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "serial_com.h"
#include "display.h"
#include "potentiometers.h"
#include <string>


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
void userInterfaceDisplayUpdate(){
    static int accumulatedDisplayTime = 0;
    wiperRead = wiperPotRead();
    timeDelayRead = timePotRead();

    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        //change all of this to reporesent the read values for the potentiometers
        if (wiperRead < WIPER_INT){
            displayCharPositionWrite ( 12,0 );
            displayStringWrite("OFF");
        } else if (wiperRead > WIPER_INT && wiperRead < WIPER_LOW){
            displayCharPositionWrite ( 12,0 );
            displayStringWrite("INT");
            if (timeDelayRead > DELAY_MEDIUM){
                displayCharPositionWrite (12,1 );
                displayStringWrite("LONG");
            } else if (timeDelayRead > DELAY_MEDIUM && timeDelayRead < DELAY_SHORT){
                displayCharPositionWrite (12,1 );
                displayStringWrite("MEDIUM");
            } else if (timeDelayRead > DELAY_SHORT){
                displayCharPositionWrite (12,1 );
                displayStringWrite("SHORT");
            }
        } else if (wiperRead > WIPER_LOW && wiperRead < WIPER_HI){
            displayCharPositionWrite ( 17,0 );
            displayStringWrite("LOW");
        } else if (wiperRead > WIPER_HI){
            displayCharPositionWrite ( 17,0 );
            displayStringWrite("HI");
        }
    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

void serialComPrint(){
    wiperRead = wiperPotRead();
    char wiperStr[100];
    int wiperStringLength;
    sprintf (wiperStr, "Wiper Potentiometer Value: %.2f\r\n", wiperRead);
    uartUsb.write(wiperStr, strlen(wiperStr));

    timeDelayRead = timePotRead();
    char timeStr[100];
    int timeStringLength;
    sprintf (timeStr, "Time Delay Potentiometer Value: %.2f\r\n", timeDelayRead);
    uartUsb.write(timeStr, strlen(timeStr));
}

//=====[Implementations of private functions]==================================
