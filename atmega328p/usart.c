#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "global.h"

ISR (USART_RX_vect)
{
    usart_recived_char=UDR0;
    usart_transmit(0x40);
    usart_transmit(usart_recived_char);
}

unsigned char usart_recive (void)
{
    while ((UCSR0A & 0X80)==0x00);
    return UDR0;
}

void usart_transmit( unsigned int data )
{
  while ((UCSR0A & 0x20) == 0x00); 
  UDR0 = data; 
}

void usart_transmit_string( char s[] )
{	
	int i = 0;
  while (i < 64)
  {
	  if (s[i] == '\0') break;
	  usart_transmit(s[i++]);
  }
}

void init_usart(unsigned int baudrate)
{
	UCSR0C &= (~(1<<UMSEL00) & ~(1<<UMSEL01));
	UCSR0A = (1<<U2X0);
	
	UBRR0H = (unsigned char) (baudrate>>8);
	UBRR0L = (unsigned char) (baudrate);
	
	UCSR0C = ((1<<UCSZ00) | (1<<UCSZ01));
	
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	sei();
	UCSR0B |= (1<<RXCIE0);
}