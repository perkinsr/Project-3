//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"
#include "display.h"
#include "potentiometers.h"

//=====[Declaration of private defines]========================================

//all private defines have to deal with the initialization and writing functions

#define DISPLAY_IR_CLEAR_DISPLAY   0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL 0b00001000
#define DISPLAY_IR_FUNCTION_SET    0b00100000
#define DISPLAY_IR_SET_DDRAM_ADDR  0b10000000

#define DISPLAY_IR_ENTRY_MODE_SET_INCREMENT 0b00000010
#define DISPLAY_IR_ENTRY_MODE_SET_DECREMENT 0b00000000
#define DISPLAY_IR_ENTRY_MODE_SET_SHIFT     0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT  0b00000000

#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF 0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_ON   0b00000010
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF  0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_ON    0b00000001
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF   0b00000000

#define DISPLAY_IR_FUNCTION_SET_8BITS    0b00010000
#define DISPLAY_IR_FUNCTION_SET_4BITS    0b00000000
#define DISPLAY_IR_FUNCTION_SET_2LINES   0b00001000
#define DISPLAY_IR_FUNCTION_SET_1LINE    0b00000000
#define DISPLAY_IR_FUNCTION_SET_5x10DOTS 0b00000100
#define DISPLAY_IR_FUNCTION_SET_5x8DOTS  0b00000000

#define DISPLAY_20x4_LINE1_FIRST_CHARACTER_ADDRESS 0
#define DISPLAY_20x4_LINE2_FIRST_CHARACTER_ADDRESS 64
#define DISPLAY_20x4_LINE3_FIRST_CHARACTER_ADDRESS 20
#define DISPLAY_20x4_LINE4_FIRST_CHARACTER_ADDRESS 84

#define DISPLAY_RS_INSTRUCTION 0
#define DISPLAY_RS_DATA        1

#define DISPLAY_RW_WRITE 0
#define DISPLAY_RW_READ  1

#define DISPLAY_PIN_RS  4
#define DISPLAY_PIN_RW  5
#define DISPLAY_PIN_EN  6
#define DISPLAY_PIN_D0  7  
#define DISPLAY_PIN_D1  8  
#define DISPLAY_PIN_D2  9  
#define DISPLAY_PIN_D3 10
#define DISPLAY_PIN_D4 11
#define DISPLAY_PIN_D5 12 
#define DISPLAY_PIN_D6 13 
#define DISPLAY_PIN_D7 14 

//=====[Declaration and initialization of public global objects]===============

DigitalOut displayD0( D0 );
DigitalOut displayD1( D1 );
DigitalOut displayD2( D2 );
DigitalOut displayD3( D3 );
DigitalOut displayD4( D4 );
DigitalOut displayD5( D5 );
DigitalOut displayD6( D6 );
DigitalOut displayD7( D7 );
DigitalOut displayRs( D8 );
DigitalOut displayEn( D9 );

//=====[Declarations (prototypes) of private functions]========================

static void displayPinWrite( uint8_t pinName, int value );
static void displayDataBusWrite( uint8_t dataByte );
static void displayCodeWrite( bool type, uint8_t dataBus );

//=====[Implementations of public functions]===================================

//takes in the wiper state and interval value, if indicated, and displays the correcponding state
//on the display
void displayWrite (int placement, int interval) {

    if (placement == WIPER_STATE_OFF){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite("OFF");
        displayCharPositionWrite(12,1);
        displayStringWrite("N/A");
    } else if (placement == WIPER_STATE_INTER){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite("INT");
        if (interval == INTER_STATE_LONG){
            displayCharPositionWrite (12,1 );
            displayStringWrite("LON");
        } else if (interval == INTER_STATE_MEDIUM){
            displayCharPositionWrite (12,1 );
            displayStringWrite("MED");
        } else if (interval == INTER_STATE_SHORT){
            displayCharPositionWrite (12,1 );
            displayStringWrite("SHO");
        }
    } else if (placement == WIPER_STATE_LOW){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite("LOW");
        displayCharPositionWrite(12,1);
        displayStringWrite("N/A");
    } else if (placement == WIPER_STATE_HI){
        displayCharPositionWrite ( 12,0 );
        displayStringWrite("HIG");
        displayCharPositionWrite(12,1);
        displayStringWrite("N/A");
    }
}

//initializes the display
void displayInit()
{
    delay( 50 );
    
    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 5 );
            
    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 1 ); 

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS );
    delay( 1 );  

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_FUNCTION_SET | 
                      DISPLAY_IR_FUNCTION_SET_8BITS | 
                      DISPLAY_IR_FUNCTION_SET_2LINES |
                      DISPLAY_IR_FUNCTION_SET_5x8DOTS );
    delay( 1 );         

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_DISPLAY_CONTROL |
                      DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF |      
                      DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |       
                      DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );       
    delay( 1 );          

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_CLEAR_DISPLAY );       
    delay( 1 ); 

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_ENTRY_MODE_SET |
                      DISPLAY_IR_ENTRY_MODE_SET_INCREMENT |       
                      DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT );                  
    delay( 1 );           

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                      DISPLAY_IR_DISPLAY_CONTROL |
                      DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON |      
                      DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |    
                      DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );    
    delay( 1 );  
}

//takes in the x and y values as parameters and sets up the display to write at that specific position
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY )
{    
    switch( charPositionY ) {
        case 0:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE1_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
       
        case 1:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE2_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
       
        case 2:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE3_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;

        case 3:
            displayCodeWrite( DISPLAY_RS_INSTRUCTION, 
                              DISPLAY_IR_SET_DDRAM_ADDR |
                              ( DISPLAY_20x4_LINE4_FIRST_CHARACTER_ADDRESS +
                                charPositionX ) );
            delay( 1 );         
        break;
    }
}

//while the string still has variables to write, 
void displayStringWrite( const char * str )
{
    while (*str) {
        displayCodeWrite(DISPLAY_RS_DATA, *str++);
    }
}

//initializes the display by initializing the display first, then writing the two mode selections
void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Wiper Mode:" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Time Delay:" );
    
}

//=====[Implementations of private functions]==================================

//sets up the coding portion of the initialize function
static void displayCodeWrite( bool type, uint8_t dataBus )
{
    if ( type == DISPLAY_RS_INSTRUCTION )
        displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_INSTRUCTION);
        else // if i broke something here go look at original code for this 
        displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_DATA);
    displayPinWrite( DISPLAY_PIN_RW, DISPLAY_RW_WRITE );
    displayDataBusWrite( dataBus );
}

//sets up the display pins
static void displayPinWrite( uint8_t pinName, int value )
{
    switch( pinName ) {
        case DISPLAY_PIN_D0: displayD0 = value;   break;
        case DISPLAY_PIN_D1: displayD1 = value;   break;
        case DISPLAY_PIN_D2: displayD2 = value;   break;
        case DISPLAY_PIN_D3: displayD3 = value;   break;
        case DISPLAY_PIN_D4: displayD4 = value;   break;
        case DISPLAY_PIN_D5: displayD5 = value;   break;
        case DISPLAY_PIN_D6: displayD6 = value;   break;
        case DISPLAY_PIN_D7: displayD7 = value;   break;
        case DISPLAY_PIN_RS: displayRs = value;   break;
        case DISPLAY_PIN_EN: displayEn = value;   break;
        case DISPLAY_PIN_RW: break; 
        default: break;
    }
}

//sets up the display buses
static void displayDataBusWrite( uint8_t dataBus )
{
    displayPinWrite( DISPLAY_PIN_EN, OFF );
    displayPinWrite( DISPLAY_PIN_D7, dataBus & 0b10000000 );
    displayPinWrite( DISPLAY_PIN_D6, dataBus & 0b01000000 );
    displayPinWrite( DISPLAY_PIN_D5, dataBus & 0b00100000 );
    displayPinWrite( DISPLAY_PIN_D4, dataBus & 0b00010000 );
    displayPinWrite( DISPLAY_PIN_D3, dataBus & 0b00001000 );
    displayPinWrite( DISPLAY_PIN_D2, dataBus & 0b00000100 );  
    displayPinWrite( DISPLAY_PIN_D1, dataBus & 0b00000010 );      
    displayPinWrite( DISPLAY_PIN_D0, dataBus & 0b00000001 );
    displayPinWrite( DISPLAY_PIN_EN, ON );              
    delay( 1 );
    displayPinWrite( DISPLAY_PIN_EN, OFF );  
    delay( 1 );                   
}