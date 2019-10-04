/*
 * UART.c
 *
 * Created: 07-09-2019 17:17:45
 * Author : DESD
 */ 


#include <avr/io.h>
//#include <util/delay.h>
#include <stdlib.h>
void delay(int);

#define F_CPU 16000000 // Clock Speed
void USART_Init();
void USART_Transmit( unsigned char);
unsigned char USART_Receive();


int main(void)
{
	//int i=0,len=9;
	//unsigned char ch[30] = "abcdefghi123456789";
	unsigned char ch;
	USART_Init( );
	PORTC = 0xFF;
	while(1)
	{
		
		USART_Transmit('B');
		delay(1000);
		ch = USART_Receive();
		PORTC = ch;
	}
	return 0;
}

void USART_Init( )
{	DDRC = 0xFF;
	//PORTC = 0x88;
	UBRR1H = 0x00;                             /* Set baud rate */
	UBRR1L = 0x67;                              //Baud rate 9600   
	UCSR1B = (1<<RXEN1)| (1<<TXEN1);         // Enable receiver and transmitter 
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);         //Set frame format: 8data, 1-stop bit 
}

void USART_Transmit( unsigned char data )
{
	//UDR1 = data;                     /* Put data into buffer, sends the data */
	//while (!(UCSR1A & (1<<TXC1))); /* Wait for empty transmit buffer */
	while ( !(UCSR1A & (1<<UDRE1)) );
	//{       UDR1 = data;
		if(!(UCSR1A & (0<<TXC1)))
		{
			UDR1 = data; 
			UCSR1A&=~(1<<TXC1);    //CLEAR TXC1 BY WRITTING 1
			
		}
		  
		//delay(1000);
		//UCSR1A &=~(1<<UDRE1);
	//}
}

unsigned char USART_Receive()
{	//char ch='A';
	//PORTC=0xff;
	//unsigned char ch;
	while ( !(UCSR1A & (1<<UDRE1)) ); 
	UCSR1A&=(1<<RXC1);    //CLEAR RXC1 BY WRITTING 1
	return(UDR1);
}


void delay(int x)
{
	TCCR1A = 0X00;
	TCCR1B = 0X01;  // No prescaling
	TCNT1 = 0xC180;
	for(unsigned int i=0 ; i<x ; i++)
	{
		while(((TIFR & (1<<2)) != 0X04));
		TCNT1 = 0xC180;
		TIFR = 0X04;
	}
}
