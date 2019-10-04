/*
 * BUZZZZZZZZZZZZZZZZZZZ.c
 *
 * Created: 02-09-2019 02:27:44
 * Author : DESD
 */ 
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/io.h>


int main(void)
{	unsigned int i;// c;
	DDRA = 0XFF;
	PORTA= 0xff;
	while(1)
	{	for(i=1; i<50; i++)
		{	//c = i*10;
			_delay_ms(500);
			PORTA = 0x00;
			_delay_ms(500);
			PORTA = 0xff;
		}
	}
}
