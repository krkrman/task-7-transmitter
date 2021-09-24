/*
 * drivers V1.c
 *
 * Created: 9/20/2021 1:33:51 PM
 * Author : Karim Essam
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/USART/USART_interface.h"
#include "MCAL/SPI/SPI_interface.h"
#include "HAL/LCD/LCD_interface.h"
#include "HAL/LED/LED_interface.h"
#include "MCAL/DIO/DIO_interface.h"

int main(void)
{
    /* Replace with your application code */
	USART_voidInit(TRANSMIT_RECIEVE , ASYNCRONOUS , EIGHT_BITS , DISAPLED , ONE_STOP_BIT , 2400);	
	SPI_voidInit(MASTER_MODE , MSB , LEADING_IS_RISING , LEADING_IS_SAMPLE , SPI_PRESCALAR_16);
	
	u8 string[20];
	u8 index = 0;
    while (1) 
    {
		u8 data = USART_u8RecieveData();
		// if backspace
		if (data == 0x08)
			index--;
		// add data if it is not enter
		else if (data != '\r')
			string[index++] = data;
		if (data == '\r' && string[0] != NULL)
		{
			string[index] = NULL;
			SPI_voidMasterTransmitString(string);
			memset(string, NULL, sizeof(string));
			index = 0;
		}
		
    }
}
