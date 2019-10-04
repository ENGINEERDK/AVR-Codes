/*
 * extInti.c
 *
 * Created: 12-09-2019 08:32:59 PM
 * Author : DESD
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void)
{
	DDRE= 0x00;		//Configure Port E as input port
	PORTE=0xff;		//Enable pull up resistor

	DDRC=0xff;		//Configure Port C as output port
	PORTC= 0xff;
	
	EICRB=0x00;
	EIMSK=0xC0;
	sei();
	
	while(1)
	{
		
	}
}


ISR(INT6_vect)			//INT6
{
	cli();
	PORTC=0xF7;
	sei();
}

ISR(INT7_vect)			//INT7
{
	cli();
	PORTC=0xFB;
	sei();
}

