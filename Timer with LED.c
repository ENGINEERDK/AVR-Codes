/*
 * LedDel.c
 *
 * Created: 04-09-2019 14:10:16
 * Author : DESD
 */ 


#include <avr/io.h>
#define F_CPU 16000000
//#include <util/delay.h>
void delay(unsigned int);
int main(void)
{ 
	DDRC=0xff;			//Configure portc as output port
	PORTC= 0x00;
	while(1)
	{
		 delay(2000);
	// _delay_ms('2000');
	PORTC=~PORTC;	 
	}
		
}
void delay(unsigned int x)
{
	unsigned int i;
	
	TCNT1=0xC180;
	TCCR1A=0x00;
	TCCR1B=0x01;
	for(i=0;i<x ;i++)
	{
		while(((TIFR&(1<<2)) != 0x04));
		TIFR=0x04;
		TCNT1=0xC180;
		
	}
}