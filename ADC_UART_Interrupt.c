/*
 * ADC_UART_Interrupt.c
 *
 * Created: 9/18/2019 1:17:42 PM
 * Author : PRN190840130031_PRN190840130032
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>	//including interrupt header file

#define F_CPU 16000000
#define BAUD 9600						// Set Baud rate
#define MYBAUD F_CPU/16/BAUD-1


void delay(int);						//declaration of delay function
void USART_Init(unsigned int ubrr);		//declaration of UART initialization function
void USART_Transmit( unsigned char);	//declaration of USART transmission function


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

ISR(ADC_vect)				//ADC interrupt vector
{
	cli();					//disable global interrupt
	unsigned int i=0,len;
	int Ain,AinLow;
	char String[5];
	delay(200);									//200 ms delay
	AinLow = (int)ADCL;									/* Read lower byte*/
	Ain = (int)ADCH*256;									/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;									//Add higher and lower byte
	itoa(Ain,String,10);
	
	len = strlen(String);					//length of the string
	USART_Init( MYBAUD );				//calling initialization function
	PORTC = 0xFF;
	while(i<=len)
	{
		USART_Transmit(String[i]);		//transmitting the string one char at once till the string does not end
		i++;
	}
	delay(1000);
	sei();					//enable global interrupt
}
void delay(int x)
{
	TCCR1A = 0X00;
	TCCR1B = 0X01;						//selecting 1 pre scaler
	TCNT1 = 0xC180;						//count for 1 ms
	for(unsigned int i=0 ; i<x ; i++)
	{
		while(((TIFR & (1<<2)) != 0X04)); //check till TIFR is set
		TCNT1 = 0xC180;						//assign the count register again
		TIFR = 0X04;						//clear the TIFR register
	}
}
void USART_Init( unsigned int ubrr )	//UART Initialization function
{
	UBRR1H = (unsigned char)(ubrr>>8);	//setting the upper 8-bit of MYBAUD
	UBRR1L = (unsigned char)ubrr;		//setting the lower 8-bit of MYBAUD
	UCSR1B = (1<<RXEN1)| (1<<TXEN1);	// Enable receiver and transmitter
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);	// Set frame format: 8data, 1-stop bit
}

void USART_Transmit( unsigned char data )
{
	while ( !(UCSR1A & (1<<UDRE1)) );	//checking the UDR register is empty
	UDR1 = data;						//Assigning the data to URD register
	
}