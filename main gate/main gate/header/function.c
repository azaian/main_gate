/*
* function.c
*
* Created: 7/21/2018 8:36:52 PM
*  Author: zaian
*/

#include "function.h"
#include "lcd.h"
#include "EEPROM.h"
#include "pins.h"
void get_stored_password(uint8_t* pass){
	
	char len = EEPROM_read(passLenAddr);
	EEPROM_readNByte(passAddrLoc,(uint8_t*)pass,len);
	pass[len]='\0';

}

int initpassword()
{
	_delay_ms(2000); // wait for check new password update

	if (BIT_IS_SET(PIND,PD5))	return 0; // if pin is set change nothing if not return 1 to change password
	
	LCD_clearScreen();
	LCD_displayString("press any key");
	LCD_displayStringRowColumn(1,0,"to change pass");
	return 1;
}

void open_gate()
{
	SET_BIT(gateLockPORT,gateLockP);
	_delay_ms(2000);
	CLEAR_BIT(gateLockPORT,gateLockP);

	
}

void alarm()
{
	SET_BIT(buzzerPORT,buzzerP);
	_delay_ms(1500);
	CLEAR_BIT(buzzerPORT,buzzerP);	
}

void buzz()
{
	SET_BIT(buzzerPORT,buzzerP);
	_delay_ms(100);
	CLEAR_BIT(buzzerPORT,buzzerP);
}

void MCU_power_down(){
	SET_BIT(MCUCR,SE);
	//SM0..2 010 for power_down mode
	CLEAR_BIT(MCUCR,SM0);
	SET_BIT(MCUCR,SM1);
	CLEAR_BIT(MCUCR,SM2);
}

void MCU_wake_up()
{
	CLEAR_BIT(MCUCR,SE);
}