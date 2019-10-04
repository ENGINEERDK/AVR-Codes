/*
 * LCD+UART+EXTR.c
 *
 * Created: 14-09-2019 14:14:13
 * Author : DESD
 */ 
/*
 * uartreclcd.c
 *
 * Created: 13-09-2019 07:48:18 PM
 * Author : DESD
 */ 

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>


//Function Initialization for LCD & UART
void uart_init (void);
void uart_recieve(void);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void clear_bit(unsigned int);
void set_bit(unsigned int);
void enable(void);
void lcd_string(char *);
void lcd_goto(unsigned int x, unsigned int y);

// define some macros
#define BAUD 9600 // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // set baud rate value for UBRR

int main(void)
{
	DDRA=0Xff;
	DDRC=0xff;
	EICRB=0x00;
	EIMSK=0xC0;
	uart_init();
	lcd_init();
	lcd_cmd(0x14);
	lcd_cmd(0x06);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	//lcd_string("Dhoni finishes");
	//lcd_goto(1,0);
	//lcd_string("off in his sytle");
	
	DDRE= 0x00;		//Configure Port E as input port
	PORTE=0xff;		//Enable pull up resistor
		
 	while(1){
		uart_recieve();
}
}

void uart_init (void)
{
	// set baud rate
	
	UBRR1H = (BAUDRATE>>8);								// shift the register right by 8 bits
	UBRR1L = BAUDRATE;									//setting the lower
	UCSR1C|=(1<<USBS1) | (1<<UCSZ10) | (1<<UCSZ11);	//setting data size stop bit
	UCSR1B|= (1<<RXEN1);						// enable receiver and transmitter
	
}

void lcd_cmd(unsigned char ch)
{
	PORTA= (ch&0xf0);			// sending Higher nibble first
	clear_bit(0);				//Command Register select
	enable();				//Enable pulse
	ch = ch<<4;
	PORTA= (ch&0xf0);			//Sending lower nibble afterwards
	clear_bit(0);
	enable();
}

void enable(void)
{
	set_bit(2);
	_delay_ms(20);
	clear_bit(2);
	_delay_ms(20);
}


void set_bit(unsigned int bit)
{
	PORTA= PORTA|(1<<bit);
}

void clear_bit(unsigned int bit)
{
	PORTA= PORTA&(~(1<<bit));
}

void lcd_init()
{
	lcd_cmd(0x28);// Divide the LCD into 2 parts Highner and Lower
	clear_bit(0);// Selct Instruction Mode 0
	enable();//
}

void lcd_string(char *str)
{
	while(*str!='\0')
	{
		lcd_data(*str++);
	}
}


void lcd_goto(unsigned int x, unsigned int y)
{
	if(x==0)
	lcd_cmd(0x80|y);
	if(x==1)
	lcd_cmd(0xc0|y);
}

void lcd_data(unsigned char ch)
{
	PORTA= (ch&0xf0);
	set_bit(0);
	enable();
	ch = ch<<4;
	PORTA= (ch&0xf0);
	set_bit(0);
	enable();
}
void uart_recieve (void)
{	char c;
	
	while(!(UCSR1A & (1<<RXC1)));
	
       c=UDR1;					// wait while data is being received
        PORTC = c;
	sei();	
	while(1)
	{
		
	}	
}
ISR(INT7_vect)			//INT7
{	
	char c;
	//lcd_cmd(0x01);
	c=UDR1;
	cli();
	lcd_data(c);
	
	uart_recieve();
	sei();
}