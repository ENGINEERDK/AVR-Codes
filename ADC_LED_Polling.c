/*
 * ADC_LDC_polling.c
 *
 * Created: 9/18/2019 12:00:27 PM
 * Author : PRN190840130031_PRN190840130032
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC=0xff;													//Setting Port C as output
	ADCSRA|=(1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0);	//Enabling the ADC and Pre scaling to make the clock freq between 50-250KHz
	ADMUX|=(1<<REFS1) | (1<<REFS0);								//selecting 2.56V as V reference
	while (1)
	{
		ADCSRA|=(1<<ADSC);										//Start ADC Conversion
		while((ADCSRA & (1<<ADIF))==0);							//Check while if ADC Interrupt flag set (conversion complete)
		_delay_ms(200);											//delay of 200 ms
		PORTC=ADCL;												//Assign the lower 8 bit of conversion
		_delay_ms(200);											//delay of 200 ms
		PORTC=ADCH;												//Assign the upper 2 bit of ADC Conversion
	}
}

