//=====[#include guards - begin]===============================================

#ifndef _POTENTIOMETERS_H_
#define _POTENTIOMETERS_H_

//=====[Declaration of public defines]=========================================
#define DELAY_SHORT  0.7
#define DELAY_MEDIUM 0.4


#define WIPER_HI  0.75
#define WIPER_LOW 0.55
#define WIPER_INT 0.3
//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
float wiperPotRead();
float timePotRead();
//=====[#include guards - end]=================================================

#endif // _MODULE_TEMPLATE_H_