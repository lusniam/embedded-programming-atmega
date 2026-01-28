#include "usart.h"
#include "timer.h"
#include "queue.h"

int timer_count = 0;
queue* rx_queue;

ISR(USART_RXC_vect)
{
	static char a;
	a = UDR;
	received_byte = a;
	PORTA = received_byte;
}

ISR(TIMER0_OVF_vect){
	if(timer_count<160){
		timer_count++;	
	}
	else{
		UDR = PORTA;
		timer_count=0;
	}
	TCNT0 = 244;
}

#include <util/delay.h>
int main(void)
{
	usart_init();
	timer_init();
	DDRA=255;
	sei();
	
    while (1)
    {
		
    }
}

