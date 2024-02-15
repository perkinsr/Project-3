//=====[#include guards - begin]===============================================

#ifndef _POTENTIOMETERS_H_
#define _POTENTIOMETERS_H_

//=====[Declaration of public defines]=========================================
#define DELAY_SHORT  0.7
#define DELAY_MEDIUM 0.4

// Macros for wiper states
#define WIPER_STATE_OFF       1
#define WIPER_STATE_INTER     2
#define WIPER_STATE_LOW       3
#define WIPER_STATE_HI        4

// Macros for intermediate mode states
#define INTER_STATE_SHORT     1
#define INTER_STATE_MEDIUM    2
#define INTER_STATE_LONG      3


#define WIPER_HI  0.75
#define WIPER_LOW 0.55
#define WIPER_INT 0.3
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
float wiperPotRead();
float intermediatePotRead();
//void potentiometerCheck();
int readWiperState(float wiperRead);
int readIntermediateState(float intermediateMode);
//=====[#include guards - end]=================================================

#endif // _MODULE_TEMPLATE_H_