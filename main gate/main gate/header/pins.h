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

#define _outDoorLightDIR DDRB
#define _outDoorLightPORT PORTB
#define _outDoorLightpin PB0

#define _poolDIR DDRB
#define _poolPORT PORTB
#define _poolpin PB3

#define _alarmDIR DDRD
#define _alarmPORT PORTD
#define _alarmpin PD7

#define _inDoorDIR DDRD
#define _inDoorPORT PORTD
#define _inDoorpin PD6

#define _livingDIR DDRD
#define _livingPORT PORTD
#define _livingpin PD4


#define open(port,pin) CLEAR_BIT(port,pin)
#define close(port,pin) SET_BIT(port,pin)

void init_pins();


#endif /* PINS_H_ */