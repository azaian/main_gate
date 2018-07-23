/*
* function.c
*
* Created: 7/21/2018 8:36:52 PM
*  Author: zaian
*/
#include "function.h"
#include "lcd.h"
#include "EEPROM.h"
#include "keypad.h"
void get_stored_password(uint8_t* pass){
	
	char len = EEPROM_read(passLenAddr);
	EEPROM_readNByte(passAddrLoc,(uint8_t*)pass,len);
	pass[len]='\0';

}


void initpassword()
{
	char str[20];
	int i=0;
	char ch;
	CLEAR_BIT(DDRD,PD5);
	SET_BIT(PORTD,PD5); // enable pull up resistor on pd5 pin
	_delay_ms(3000);
	if (BIT_IS_CLEAR(PIND,PD5))// set new password
	{
		LCD_clearScreen();
		LCD_displayString("enter new password");
		return 1;
	}
	else
	{
		LCD_clearScreen();
		LCD_displayString("use your password");
		return 0;
	}


}