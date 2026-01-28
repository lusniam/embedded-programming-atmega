#ifndef USART_H
#define USART_H
#define F_CPU 4000000UL
#include <avr/io.h>
#define BAUDRATE 9600
#define BAUDRATE_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)
extern uint8_t received_byte;
void usart_init();
void usart_transmit_char(uint8_t character);
uint8_t usart_receive_char();
void usart_transmit_string(char* string, uint32_t length);

#endif