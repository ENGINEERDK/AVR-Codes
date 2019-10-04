/*
 * ADC_LCD_Interrupt.c
 *
 * Created: 9/18/2019 1:53:47 PM
 * Author : PRN190840130031_PRN190840130032
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>	//including interrupt header file




//Function Initialization for LCD
void lcd_init(void);									//declaration of LCD initialization
void lcd_cmd(unsigned char);							//declaration of LCD Command transmit function
void lcd_data(unsigned char);							//declaration of LCD Data Transmit function
void clear_bit(unsigned int);							//declaration to clear a bit function
void set_bit(unsigned int);								//declaration to set a bit function
void enable(void);										//declaration to enable LCD
void lcd_string(char *);								//declaration to transmit string function
void lcd_goto(unsigned int x, unsigned int y);

int main(void)
{
	DDRA=0xff;
	lcd_init();
	lcd_cmd(0x14);
	lcd_cmd(0x06);
	lcd_cmd(0x0e);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
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
	int Ain,AinLow;
	char String[5];
	AinLow = (int)ADCL;									/* Read lower byte*/
	Ain = (int)ADCH*256;									/* Read higher 2 bits and Multiply with weight */
	Ain = Ain + AinLow;									//Add higher and lower byte
	itoa(Ain,String,10);									//convert Ain in string
	lcd_string("Digital Value:");							//display digital value on Lcd
	lcd_goto(1,0);											//next line
	lcd_string(String);										//display the string
	sei();					//enable global interrupt
}
void lcd_cmd(unsigned char ch)
{
	PORTA= (ch&0xf0);			// sending Higher nibble first
	clear_bit(0);				//Command Register select
	enable();				    //Enable pulse
	ch = ch<<4;					//shift the lower nibble to upper nibble
	PORTA= (ch&0xf0);			//Sending Lower nibble afterwards
	clear_bit(0);				//Command Register select
	enable();					//enable lcd
}

void enable(void)
{
	set_bit(2);					//set enable pin
	_delay_ms(20);				//delay of 20 ms
	clear_bit(2);				//clear enable pin
	_delay_ms(20);				//delay of 20 ms
}


void set_bit(unsigned int bit)
{
	PORTA= PORTA|(1<<bit);			//set a bit
}

void clear_bit(unsigned int bit)
{
	PORTA= PORTA&(~(1<<bit));		//clear a bit
}

void lcd_init()
{
	lcd_cmd(0x28);					// Divide the LCD into 2 parts Highner and Lower
	clear_bit(0);					// Select Instruction Mode 0
	enable();						// Enable LCD
}

void lcd_string(char *str)
{
	while(*str!='\0')
	{
		lcd_data(*str++);		//transmit string char till null
	}
}


void lcd_goto(unsigned int x, unsigned int y)
{
	if(x==0)
	lcd_cmd(0x80|y);				//clear screen command
	if(x==1)
	lcd_cmd(0xc0|y);				//2nd line command
}

void lcd_data(unsigned char ch)
{
	PORTA= (ch&0xf0);				// transmit upper nibble to lcd
	set_bit(0);						// select data mode
	enable();						// enable the lcd
	ch = ch<<4;						// shift the lower nibble to upper nibble
	PORTA= (ch&0xf0);				// transmit the upper nibble to lcd
	set_bit(0);						// select data mode
	enable();						// enable the lcd
}