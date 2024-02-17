//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declarations (prototypes) of public functions]=========================

void displayInit( void );
 
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

void displayStringWrite( const char * str );

void displayWrite(int placement, int interval);

void userInterfaceDisplayInit();

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_