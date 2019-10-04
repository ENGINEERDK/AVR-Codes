/*
 * LCD+UART.c
 *
 * Created: 14-09-2019 11:19:35
 * Author : DESD
 */ 

/*
 * lcd_1.c
 *
 * Created: 12-09-2019 07:17:54 PM
 * Author : 29_30
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


//Function Initialization for LCD
void uart_receive(void);
void uart_init(void);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void clear_bit(unsigned int);
void set_bit(unsigned int);
void enable(void);
//void lcd_string(char *);
//void lcd_goto(unsigned int x, unsigned int y);

int main(void)
{
	
	
	DDRA=0xff;
	lcd_init();
	lcd_cmd(0x14);
	lcd_cmd(0x06);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	//lcd_string("bonny");
	//lcd_goto(1,0);
	//lcd_string("pando");
	
   while(1)
	   uart_receive();
}

void uart_init()
{	DDRC = 0xFF;
	//PORTC = 0x88;
	UBRR1H = 0x00;   /* Set baud rate */
	UBRR1L = 0x67;   //Baud rate 9600
	
	UCSR1C = (1<<USBS1)|(1<<UCSZ10)|(1<<UCSZ11);  /* Set frame format: 8data, 1-stop bit  */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);   /* Enable receiver and transmitter */
}
void uart_receive(void)
{	char c;
	//char ch='A';
	//PORTC=0xff;
	//unsigned char ch;
	while ( !(UCSR1A & (1<<RXC1)));
	c=UDR1;
	PORTC=c;
	lcd_data(c);
	//return(UDR1);
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