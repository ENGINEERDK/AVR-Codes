/*
 * Timer Normal mode with interrupt.c
 *
 * Created: 10-09-2019 14:29:35
 * Author : DESD
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//#define sbi(port,bit) port |= (1<<bit)
//#define cbi(port,bit) port &= ~(1<<bit)
unsigned int count=0;

int main(void)
{	DDRC = 0xFF;			//set port c as output
	PORTC = 0x00;			//switch on led by pulling port c low
	sei();					//sei() to set global interrupt
	TCNT1 = 0xC17F;			//initial count
	TIMSK = 0x04;			//enable T1 overflow INTERRUPT
	TCCR1B = 0x01;			//timer start with no pre-scalar
	/* Replace with your application code */
	while (1);
}

ISR(TIMER1_OVF_vect)
{	//char status_reg = SREG;
	count++;
	if(count == 1000)
	{	PORTC = ~PORTC;
		count = 0;
	}
	TCNT1 = 0xC17F;
	//char SREG = status_reg;
}

