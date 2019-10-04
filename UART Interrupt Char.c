/*UART_INTERRUPT(TX / RX)_1CHAR ,
 * UART.c
 *
 * Created: 07-09-2019 17:17:45
 * Author : DESD
 */ 


#include <avr/io.h>
//#include <util/delay.h>
#include <stdlib.h>
#include<avr/interrupt.h>
void delay(int);

#define F_CPU 16000000 // Clock Speed
void USART_Init();
void USART_Transmit( unsigned char);
//void USART_Receive();


int main(void)
{
	
	USART_Init( );
	
	//delay(1000);
	USART_Transmit('A');
	//USART_Receive();
	
	while(1);
	return 0;
}

void USART_Init( )
{	DDRC = 0xFF;
	PORTC = 0x10;
	delay(1000);
	//delay(1000);
	

	UBRR1H = 0x00;   /* Set baud rate */
	UBRR1L = 0x67;   //Baud rate 9600   
	UCSR1B = (1<<RXEN1) |(1<<TXEN1) | (1<<UDRIE1) | (1<<RXCIE1);   /* Enable receiver,transmitter and interrupt*/  
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);  /* Set frame format: 8data, 1-stop bit  */
}

void USART_Transmit( unsigned char data )
{
		UDR1 = 'a'; 
		sei();
			
}

/*void USART_Receive()
{	
	PORTC=0xF0;
	delay(1000);
	delay(1000);
	delay(1000);
	sei();
	//PORTC=~PORTC;
	//delay(1000);
	//delay(1000);
	//delay(1000);
}*/

ISR(USART1_TX_vect)      //Transmit Interrupt
{
	PORTA = 0x85;
	delay(1000);
		
}



/*ISR(USART1_RX_vect)        //Received Interrupt
{
	char ch=UDR1;
	PORTC=ch;
	delay(3000);
	//PORTC = 0x66;
	delay(10000);
	
	
}*/

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
