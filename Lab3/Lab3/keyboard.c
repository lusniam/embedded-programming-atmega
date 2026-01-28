#include "keyboard.h"

// "row" i "column" to liczby z zakresu 1-4
bool is_key_pressed(uint8_t row, uint8_t column){
	return ( *KEYBOARD_PIN & ( _BV(row-1) ) ) == 0;
}

char get_key(){
	char pressed_key=0;
	for(int i=0;i<16;i++){
		if(is_key_pressed( (i/4)+1, (i%4)+1 )){
			if(pressed_key!=0){
				return 0xFF;
			}
			pressed_key=(char)(i+1);
		}
		// funkcja sprawdzania wielu przycisków, nie mogłem się cofnšć do poprzedniego zadania żeby zaaktualizować kod
		else if ( *KEYBOARD_PIN == 255 ){
			return 0xFF;
		}
		
	}
	return pressed_key;
}