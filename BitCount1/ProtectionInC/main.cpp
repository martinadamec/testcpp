#include "cmsis.h"
#include "algorithms/bitCount.h"

extern "C"{
	void HardFault_Handler(void){
		LPC_GPIO1->FIODIR |= 1<<21;
		LPC_GPIO1->FIOSET |= 1<<21;
		while(1);
	}
}

void toggleLed4(){
	char cur = (LPC_GPIO1->FIOPIN >> 23) & 1;
	if (cur == 0){
		LPC_GPIO1->FIOSET |= (1<<23);
	}
	else{
		LPC_GPIO1->FIOCLR |= (1<<23);
	}
}

int main(void){
	long number = 1125000;
	int bits = 0;
	LPC_GPIO1->FIODIR |= 1<<23;
	while(1){
		toggleLed4();
		bits = bit_count(number);
		if(bits != 7){
			while(1);		
		}
	}
}
