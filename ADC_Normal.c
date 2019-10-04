/*
 * ADC_UART_NORMAL.c
 *
 * Created: 9/18/2019 12:14:12 PM
 * Author : PRN190840130031_PRN190840130032
 */ 

#define F_CPU 16000000
#include <avr/io.h>
void delay(int);						//declaration of delay function

#define BAUD 9600												// Set Baud rate
#define MYUBRR F_CPU/16/BAUD-1

void USART_Init(unsigned int);									//declaration of UART initialization function
void USART_Transmit( unsigned char ubrr);						//declaration of USART transmission function

int main(void)
{
	USART_Init(MYUBRR);											//calling USART initialization function									
	DDRC=0xff;													//Setting Port C as output
	ADCSRA|=(1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) |(1<<ADPS0);	//Enabling the ADC and Pre scaling to make the clock freq between 50-250KHz
	ADMUX|=(1<<REFS1) | (1<<REFS0);								//selecting 2.56V as V reference
	while (1)
	{
		ADCSRA|=(1<<ADSC);										//Start ADC Conversion
		while((ADCSRA & (1<<ADIF))==0);							//Check while if ADC Interrupt flag set (conversion complete)
		delay(2000);											//delay of 200 ms
		PORTC=ADCL;												//Assign the lower 8 bit of conversion
		USART_Transmit(ADCL);									//Transmitting adc to uart
		delay(2000);											//delay of 200 ms
		PORTC=ADCH;
		USART_Transmit(ADCL);									//Assign the upper 2 bit of ADC Conversion
	}
}

void USART_Init( unsigned int ubrr )		//USART Initialization function
{
	
	UBRR1H = (unsigned char)(ubrr>>8);      // Assigning higher 8bit baud rate
	UBRR1L = (unsigned char)ubrr;           //Assigning lower 8bit Baud rate
	UCSR1B = (1<<RXEN1)| (1<<TXEN1);        // Enable receiver and transmitter
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);       //Set frame format: 8data, 1-stop bit
}

void USART_Transmit( unsigned char data )	//USART Transmission function
{
	while ( !(UCSR1A & (1<<UDRE1)) );		//checking if UDR register is empty
	{
		UDR1 = data;					//Assigning the data to transmit at UDR
	}
}

void delay(int x)
{
	TCCR1A = 0X00;							//selecting normal mode
	TCCR1B = 0X01;  						//selecting 1 pre-scaler
	TCNT1 = 0xC180;
	for(unsigned int i=0 ; i<x ; i++)
	{
		while(((TIFR & (1<<2)) != 0X04));	//checking if TIFR register is set
		TCNT1 = 0xC180;						//assigning the delay again
		TIFR = 0X04;						//clearing the TIFR register
	}
}
