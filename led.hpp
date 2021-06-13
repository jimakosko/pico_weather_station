#ifndef LED_GUARD
#define LED_GUARD 

//*******************************************************************
//*************** pico led        ****************************************
//*************** 09/06/2021 *****************************************
#include "pico/stdlib.h"

class led{
uint LED_PIN ;	
uint delay;
public:
led(uint l_p=25,uint de=100);
void flash(uint de);
void flash();
	
};
#endif 
