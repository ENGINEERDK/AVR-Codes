/*
 * ADC_interrupt.c
 *
 * Created: 9/18/2019 1:07:13 PM
 * Author : PRN190840130031_PRN190840130032
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>		//including 
#include <avr/interrupt.h>	//including interrupt header file

int main(void)
{
	DDRC=0xff;				//Configure Port C as ouput
	PORTC=0xff;
	ADMUX= 0xc0;			//Setting up ADC0
	ADCSRA= 0xEF;			//enable ADC,Select Freq,interrupt enable
	sei();					//enable global interrupt
	
	while(1)
	{
	}
}

ISR(ADC_vect)				//ADC interrupt vactor
{
	cli();					//disable global interrupt
	PORTC= ADCH;			//assigning ADCH at Port c
	_delay_ms(2000);		//delay of 2000 ms
	PORTC=ADCL;				//assigning ADCL at Port c
	_delay_ms(2000);		//delay of 2000 ms
	sei();					//enable global interrupt
}
