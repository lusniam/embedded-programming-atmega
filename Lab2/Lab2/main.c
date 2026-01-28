/*
 * Lab2.c
 *
 * Created: 14.10.2024 08:33:51
 * Author : Student_PL
 */ 

#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

typedef enum {
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D,
} port_name_t;

void set_diodes(uint8_t number, port_name_t port){
	switch(port){
		case PORT_A: PORTA = number; break;
		case PORT_B: PORTB = number; break;
		case PORT_C: PORTC = number; break;
		case PORT_D: PORTD = number; break;
		default: break;
	}
}

// "row" i "column" to liczby z zakresu 1-4
bool is_key_pressed(uint8_t row, uint8_t column, port_name_t port){
	switch(port){
		case PORT_A:{
			PORTA = ~_BV(column+3);
			_delay_ms(10);
			return ( PINA & ( _BV(row-1) ) ) == 0;
		}
		case PORT_B:{
			PORTB = ~_BV(column+3);
			_delay_ms(10);
			return ( PINB & ( _BV(row-1) ) ) == 0;
		}
		case PORT_C:{
			PORTC = ~_BV(column+3);
			_delay_ms(10);
			return ( PINC & ( _BV(row-1) ) ) == 0;
		}
		case PORT_D:{
			PORTD = ~_BV(column+3);
			_delay_ms(10);
			return ( PIND & ( _BV(row-1) ) ) == 0;
		}
	};
	return 0;
}

bool column_check(port_name_t port){
	switch(port){
		case PORT_A:{
			return PINA == 255;
		}
		case PORT_B:{
			return PINB == 255;
		}
		case PORT_C:{
			return PINC == 255;
		}
		case PORT_D:{
			return PIND == 255;
		}
	};
	return 0;
}

char get_key(port_name_t port){
	char pressed_key=0;
	for(int i=0;i<16;i++){
		if(is_key_pressed( (i/4)+1, (i%4)+1, port)){
			if(pressed_key!=0){
				return 0xFF;
			}
			pressed_key=(char)(i+1);
		}
		// funkcja sprawdzania wielu przycisków, nie mog³em siê cofn¹æ do poprzedniego zadania ¿eby zaaktualizowaæ kod
		else if ( column_check(port) ){
			return 0xFF;
		}
		
	}
	return pressed_key;
}

//przycisk S13 czyœci numer oraz wynik na koniec
void calc(port_name_t keyboard, port_name_t led){
	uint32_t first_num=0, second_num=0;
	uint8_t operation=0;
	while (1){
		switch(get_key(keyboard)){
			case 1: {first_num=first_num*10+1; break;}
			case 2: {first_num=first_num*10+2; break;}
			case 3: {first_num=first_num*10+3; break;}
			case 4: {operation=1; break;}
			case 5: {first_num=first_num*10+4; break;}
			case 6: {first_num=first_num*10+5; break;}
			case 7: {first_num=first_num*10+6; break;}
			case 8: {operation=2; break;}
			case 9: {first_num=first_num*10+7; break;}
			case 10: {first_num=first_num*10+8; break;}
			case 11: {first_num=first_num*10+9; break;}
			case 12: {operation=3; break;}
			case 13: {first_num=0; break;}
			case 14: {first_num=first_num*10; break;}
			case 16: {operation=4; break;}
			default: break;
		}
		if(first_num>99999999){
			first_num=0;
		}
		if (operation!=0){
			set_diodes(0,led);
			_delay_ms(20);
			while(get_key(keyboard)){}
			break;
		}
		else{
			set_diodes(first_num,led);
			_delay_ms(20);
			while(get_key(keyboard)){}
		}
	}
	bool end_loop = false;
	while (1){
		switch(get_key(keyboard)){
			case 1: {second_num=second_num*10+1; break;}
			case 2: {second_num=second_num*10+2; break;}
			case 3: {second_num=second_num*10+3; break;}
			case 5: {second_num=second_num*10+4; break;}
			case 6: {second_num=second_num*10+5; break;}
			case 7: {second_num=second_num*10+6; break;}
			case 9: {second_num=second_num*10+7; break;}
			case 10: {second_num=second_num*10+8; break;}
			case 11: {second_num=second_num*10+9; break;}
			case 13: {second_num=0; break;}
			case 14: {second_num=second_num*10; break;}
			case 15: {end_loop=true; break;}
			default: break;
		}
		if(end_loop){
			break;
		}
		if(second_num>99999999){
			second_num=0;
		}
		set_diodes(second_num,led);
		_delay_ms(20);
		while(get_key(keyboard)){}
	}
	if(second_num==0){
		if(operation<3){
			set_diodes(first_num,led);
			_delay_ms(100);
			while(get_key(keyboard)!=13){}
		}
		else{
			set_diodes(0,led);
			_delay_ms(100);
			while(get_key(keyboard)!=13){}
		}
	}
	else{
		switch(operation){
			case 1: { set_diodes(first_num+second_num, led); break; }
			case 2: { set_diodes(first_num-second_num, led); break; }
			case 3: { set_diodes(first_num*second_num, led); break; }
			case 4: { set_diodes(first_num/second_num, led); break; }
		}
		_delay_ms(100);
		while(get_key(keyboard)!=13){}
	}
}

int main(void)
{
    DDRA = 0b11110000;
	PORTA = 0b00001111;
	DDRD = 255;
	PORTD = 0;
	port_name_t port_keyboard = PORT_A;
	port_name_t port_led = PORT_D;

    while (1)
    {
		calc(port_keyboard, port_led);
    }
	return 0;
}