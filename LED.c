/*
 * LED.c
 *
 * Created: 30-08-2019 16:23:31
 * Author : DESD
 */ 

#include <avr/io.h>
#define F_CPU	16000000
#include <util/delay.h>
int main(void)
{	unsigned int j;
    DDRC = 0xFF;
	//PORTC=0x7f;		//
	PORTC = 0x55;
	while (1)
	{	for(j=0; j<8; j++)
		{	_delay_ms(90);
			PORTC = PORTC>>1;
		}
		//PORTC = 0xfe;
		PORTC = 0xaa;
		for(j=0; j<8; j++)
		{	_delay_ms(90);
			PORTC = PORTC<<1;
		}
		//PORTC = 0x7f;
		PORTC = 0x55;
	}
   	
}

