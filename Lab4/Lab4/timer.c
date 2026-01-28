#include "timer.h"

void timer_init(void){
	TCCR0 |= (1 << CS02) | (1 << CS00);
	TIMSK |= (1 << TOIE0);
	TCNT0 = 244;
}