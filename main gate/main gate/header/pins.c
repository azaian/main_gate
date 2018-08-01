/*
 * pins.c
 *
 * Created: 7/9/2018 6:31:37 PM
 *  Author: zaian
 */ 
#include "pins.h"


void init_pins(){

	SET_BIT(gateLockDIR,gateLockP);//set gate lock pin to output
	CLEAR_BIT(gateLockPORT,gateLockP); // enable pull up resistor on gate lock pin
	
	SET_BIT(buzzerDIR,buzzerP);
	CLEAR_BIT(buzzerPORT,buzzerP);
	
	
	
	
	CLEAR_BIT(DDRD,PD2); // set PD2 INT0 as input
	
	CLEAR_BIT(DDRD,PD5);	// pin of reset password as input 
	SET_BIT(PORTD,PD5);		// 
	
}