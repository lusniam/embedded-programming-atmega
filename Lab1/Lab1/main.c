/*
 * Lab1.c
 *
 * Created: 07.10.2024 08:44:27
 * Author : Student_PL
 */ 

#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

typedef enum{
	BUTTON1=1<<0,
	BUTTON2=1<<1,
	BUTTON3=1<<2,
	BUTTON4=1<<3,
}buttons_t;

void zad1(){
	DDRA=255;
	PORTA=1;
	while(1){
		PORTA=PORTA<<1;
		if(PORTA==0){
			PORTA=1;
		}
		_delay_ms(1000);
	}
}

void zad2(){
	DDRD=0;
	PORTD=255;
	DDRA=255;
	PORTA=0;
	while (1){
		if((PIND & BUTTON1) == 0){
			_delay_ms(50);
			if((PIND & BUTTON1) == 0){
				PORTA=1;
				while((PIND & BUTTON1) == 0){};
				PORTA=0;
			}
		}
		if((PIND & BUTTON2) == 0){
			_delay_ms(50);
			if((PIND & BUTTON2) == 0){
				PORTA=2;
				while((PIND & BUTTON2) == 0){};
				PORTA=0;
			}
		}
		if((PIND & BUTTON3) == 0){
			_delay_ms(50);
			if((PIND & BUTTON3) == 0){
				PORTA=4;
				while((PIND & BUTTON3) == 0){};
				PORTA=0;
			}
		}
		if((PIND & BUTTON4) == 0){
			_delay_ms(50);
			if((PIND & BUTTON4) == 0){
				PORTA=8;
				while((PIND & BUTTON4) == 0){};
				PORTA=0;
			}
		}
	}
}

int main(void)
{
	//zad1();
    zad2();
}

