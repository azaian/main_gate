/*
 * pins.h
 *
 * Created: 7/9/2018 6:30:51 PM
 *  Author: zaian
 */ 


#ifndef PINS_H_
#define PINS_H_
#include "common_macros.h"
#include "micro_config.h"

#define gateLockDIR DDRD
#define gateLockPORT PORTD
#define gateLockPIN PIND
#define gateLockP PD6

#define buzzerDIR DDRD
#define buzzerPORT PORTD
#define buzzerPIN PIND
#define buzzerP PD7

void init_pins();


#endif /* PINS_H_ */