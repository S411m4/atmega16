/*
 * UART.c
 *
 * Created: 11/5/2021 7:05:05 AM
 * Author : salma
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)  //BaudRate

void UART_init(long USART_BAUDRATE);

int main(void)
{
	UART_init(9600); //initalize with baudrate 9600
	

    while (1) 
    {
		while (!(UCSRA & (1 << UDRE))); //wait till MCU is ready to send data
		UDR = 'A';
		_delay_ms(1000);
    }
}

void UART_init(long USART_BAUDRATE)
{
	UBRRL = BAUD_PRESCALE;  //load lower 8-bits of baudrate
	UBRRH = (BAUD_PRESCALE >> 8); //load upper 8 bits of baudrate
	UCSRB |= (1 << RXEN) | (1 << TXEN);  //turn on transmit and receive
	UCSRC |= (1 << UCSZ0) | (1 << UCSZ1) | (1 << URSEL);  //use 8-bit character size
	
}
