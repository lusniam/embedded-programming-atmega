#include "usart.h"

uint8_t received_byte = 0;
void usart_init(){
	UBRRH = (BAUDRATE_PRESCALER >> 8);
	UBRRL = BAUDRATE_PRESCALER;
	UCSRB = (1<<RXCIE) | (1<<RXEN) | (1<<TXEN);
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);
}

void usart_transmit_char(uint8_t character){
	while (! (UCSRA & (1<<UDRE)));
	UDR = character;
}

uint8_t usart_receive_char(){
	while ((UCSRA & (1 << RXC)) == 0);
	return(UDR);
}

void usart_transmit_string(char* string, uint32_t length){
	for(int i=0;i<length;i++){
		usart_transmit_char(string[i]);
	}
}