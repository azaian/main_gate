/*
 * pins.c
 *
 * Created: 7/9/2018 6:31:37 PM
 *  Author: zaian
 */ 
#include "pins.h"


void init_pins(){
	//set as out 
	SET_BIT(_outDoorLightDIR,_outDoorLightpin);
	SET_BIT(_outDoorLightPORT,_outDoorLightpin);
	
	SET_BIT(_poolDIR,_poolpin);
	SET_BIT(_poolPORT,_poolpin);
	
	SET_BIT(_alarmDIR,_alarmpin);
	SET_BIT(_alarmPORT,_alarmpin);
	
	SET_BIT(_inDoorDIR,_inDoorpin);
	SET_BIT(_inDoorPORT,_inDoorpin);
	
	SET_BIT(_livingDIR,_livingpin);
	SET_BIT(_livingPORT,_livingpin);
	
	
}