#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "global.h"

ISR (ADC_vect)
{
    uint8_t LowPart = ADCL;
    uint16_t TenBitResult = ADCH << 2 | LowPart >> 6;

    char bin_vol [10];
    float volt = (TenBitResult*5/1023);

    dtostrf(volt, 4, 1, bin_vol);

	usart_transmit_string(bin_vol);

	//Comenzará otra conversión.
	ADCSRA |= 1<<ADSC;
}

    void ADC_WithInterrupt(void)
{
	//Habilita el convertidor (encenderlo)
	ADCSRA |= 1 << ADEN;
			
	//Habilitar el prescaler fo=16,000,000Hz/50,000Hz=320;(tabla 76, pag.201)
	ADCSRA |= 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;	//Factor de división = 128
			
	//Resultado justificado a la izquierda (ADCH bit9-2, ADCL bit1-0)
	ADMUX |= 1 << ADLAR;
			
	//Seleccionar el voltaje de referencia REF1=0, REFS0=1
	//(AVCC with external capacitor at AREF pin)
	//Entrada AVcc= 5v y Aref= con un capacitor a GND
	//Internamente: Vref=0v a 5v
	ADMUX |= 1 << REFS0;
			
	//Habiltar interrupciones del ADC
	ADCSRA |= 1 << ADIE;
			
	//Comenzar la conversión
	ADCSRA |= 1 << ADSC;
}
