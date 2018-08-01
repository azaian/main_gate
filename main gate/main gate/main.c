/*
* main gate.c
*
* Created: 7/19/2018 4:36:00 PM
* Author : zaian
*/

#include "header/micro_config.h"
#include "header/lcd.h"
#include "header/keypad.h"
#include "header/EEPROM.h"
#include "header/function.h"
#include "header/pins.h"
#include "header/timer.h"




#define  maxchar 20
//global vars
union{
	char chr;
	int x;
	char str[20];
}un;

int passitr=0;
int pass_flag=0;
char password[maxchar];
char storedpass[20];
uint8_t power_down_flag =0;
uint16_t counter=0;

int main(void)
{
	//init INT 0 for keypad
	cli();
	//set bits ISC00,01 for rising edge int0 and PD2 as input
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(GICR,INT0);
	SET_BIT(GIFR,INTF0); // clear flag by setting 1 to it
	sei();

	init_pins();
	LCD_init();
	LCD_displayString("Initiate lock");
	pass_flag=initpassword();

	init_TMR1();
	/* Replace with your application code */
	LCD_clearScreen();
	LCD_displayString("SYS Starts");
	
	while (1)
	{
		
		
	}
}


// ISR for INT0 when keypad pressed
ISR(INT0_vect)
{
	buzz();
	
	LCD_power_on();
	TIMER1_reset();
	TIMER1_start();
	if(0==pass_flag)
	{

		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"psswrd is:");
		un.chr=KeyPad_getPressedKey();
		
		if ('#'==un.chr) // request password compare
		{
			LCD_goToRowColumn(1,0);
			LCD_displayString("checking password");
			_delay_ms(100);
			un.x=0; //clear flag for password testing
			get_stored_password((uint8_t*)storedpass);
			LCD_displayString(storedpass);
			LCD_clearScreen();
			if ( strlen(storedpass) == strlen(password) )
			{
				un.x++;
				if ( 0 == strcmp(password,storedpass) )
				{
					un.x++;
				}
			}
			
			if ( 2 == un.x )
			{
				LCD_clearScreen();
				LCD_displayString("opening gate");
				open_gate();
				TCNT1=65500;
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("wrong psswrd -_-");
				alarm();
				LCD_clearScreen();
				LCD_displayString("etnayl tani -_-");
			}
			
			//reset password to empty
			passitr=0;
			password[passitr]='\0';
		}
		else // continue password inserting.
		{
			password[passitr++]=un.chr;
			password[passitr]='\0';
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"psswrd is:");
			LCD_displayStringRowColumn(1,0,password);
		}
	}
	else // setting new password
	{
		cli();
		do
		{
			password[0]='\0';
			passitr=0;
			LCD_clearScreen();
			LCD_displayString("enter new psswrd");
			while(BIT_IS_SET(PIND,PD2));// wait to new key pressed
			while(BIT_IS_CLEAR(PIND,PD2));// wait to new key pressed
			while((un.chr=KeyPad_getPressedKey()) != '#')
			{
				password[passitr++]=un.chr;
				password[passitr]='\0';
				LCD_clearScreen();
				LCD_displayString("new password is");
				LCD_displayStringRowColumn(1,0,password);
				_delay_ms(100);
				while(BIT_IS_SET(PIND,PD2));// wait to new key pressed
				while(BIT_IS_CLEAR(PIND,PD2));// wait to new key pressed
			}
			LCD_clearScreen();
			LCD_displayString("new pass is :");
			LCD_displayStringRowColumn(1,0,password);
			_delay_ms(1000);
			LCD_clearScreen();
			LCD_displayString(password);
			LCD_displayStringRowColumn(1,0,"press # 2confirm");
			while(BIT_IS_SET(PIND,PD2));// wait to new key pressed
			while(BIT_IS_CLEAR(PIND,PD2));// wait for new key to be pressed
			un.chr=KeyPad_getPressedKey();
			
		} while (un.chr != '#'); // if # then exit and update password
		while(BIT_IS_SET(PIND,PD2));// wait to new key pressed
		LCD_clearScreen();
		LCD_displayString("new password ");
		LCD_displayStringRowColumn(1,0,password);
		_delay_ms(600);
		EEPROM_write(passLenAddr,strlen(password));
		EEPROM_WriteNByte(passAddrLoc,password,strlen(password));
		LCD_clearScreen();
		LCD_displayString("password updated");
		LCD_clearScreen();
		LCD_displayString("try it kda ;)");
		pass_flag=0;
		password[0]='\0';
		passitr=0;
		un.chr='\0';
		SET_BIT(GIFR,INTF0); // clear flag by setting 1 to it
		sei();
	}
}

ISR(TIMER1_OVF_vect)
{
	password[0]='\0';
	passitr=0;
	LCD_clearScreen();
	LCD_displayString("turnning off");
	_delay_ms(3000);
	TIMER1_sleep();
	LCD_power_off();
	MCU_power_down();
}