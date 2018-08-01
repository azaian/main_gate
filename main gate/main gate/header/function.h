/*
 * function.h
 *
 * Created: 7/21/2018 8:37:23 PM
 *  Author: zaian
 */ 


#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "micro_config.h"
#include "common_macros.h"


void get_stored_password(uint8_t* pass);
int initpassword();
void open_gate();
void alarm();
void buzz();
void MCU_power_down();
void MCU_wake_up();

#endif /* FUNCTION_H_ */