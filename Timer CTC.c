/*
 * Timers CTC.c
 *
 * Created: 10-09-2019 14:17:23
 * Author : DESD
 */ 

#include <avr/io.h>

void timer1_del(unsigned int );
 
int main(void)
{
	TCCR1B=(1<<WGM12)|(1<<CS10);//ctc mode and clock with no prescalar
	TCNT1= 0;
	OCR1A= 15999;
	
	DDRC=0xFF;
	PORTC=0x55;
	while(1)
	{
		timer1_del(1000);
		PORTC= ~PORTC;
	}
	
}

void timer1_del(unsigned int time_ms)
{
			for(int i=0;i<time_ms;i++)
		{
			while(!(TIFR&(1<<OCF1A)));
			
			TIFR|=(1<<OCF1A);
		}
}
	
