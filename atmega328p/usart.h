#ifndef USART_H_
#define USART_H_
void init_usart(unsigned int baudrate);
unsigned char usart_receive( void );
void usart_transmit( unsigned int data );
void usart_transmit_string( char s[] );
#endif