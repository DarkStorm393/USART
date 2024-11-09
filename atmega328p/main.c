#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "usart.h"
#include "adc.h"

volatile char usart_recived_char = 0;

int main (void)
{
    ADC_WithInterrupt();
    init_usart(207);
    while (1)
    {
        if (usart_recived_char == '0')
        {
            //Selecciona el canal 0 del ADC.
            ADMUX &= ~(1<<MUX0);
        } else if (usart_recived_char == '1')
        {
            //Selecciona el canal 1 del ADC.
	        ADMUX |= 1 << MUX0;
        }   
    }
}