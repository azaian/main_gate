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

int main(void)
{
	//init INT 0 for keypad
	cli();
	//set bits ISC00,01 for rising edge int0 and PD2 as input
	CLEAR_BIT(DDRD,PD2);
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);
	SET_BIT(GICR,INT0);
	SET_BIT(GIFR,INTF0); // clear flag by setting 1 to it
	sei();


	//set password length to EEPROM
	


	LCD_init();
	LCD_displayString("Initiate lock");
	

	pass_flag=initpassword();
	/* Replace with your application code */
	

	while (1)
	{
		
		
	}
}



// ISR for INT0 when keypad pressed
ISR(INT0_vect)
{
	
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
			}
			else
			{
				LCD_clearScreen();
				LCD_displayString("wrong password");
			}
			
			
			//reset password to empty
			passitr=0;
			password[passitr]='\0';
			
		}
		else // continue password inserting.
		{
			password[passitr++]=un.chr;
			password[passitr]='\0';
			LCD_displayStringRowColumn(0,10,password);
		}

	}
	else // setting new password
	{
		cli();
		SET_BIT(DDRD,PD2);
		LCD_clearScreen();
		LCD_displayCharacter("enter new password");
		while( (un.chr=KeyPad_getPressedKey()) != '#')
		{
			while(BIT_IS_CLEAR(PORTD,PD2));
			
		}
		
		sei();
	}

}