#include "cmsis.h"
#include "../algorithms/bitCount.h"

int* output = (int *)0x10005020;

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
	LPC_GPIO1->FIODIR |= (1<<23);

	LPC_SC->PCLKSEL1 &= (0b11<<14);  // mask
	LPC_SC->PCLKSEL1 |= (1<<14);   // set it to 1*SystemCoreClock
	
	LPC_SC->PCONP |= (1<<23);  // turn on power
	LPC_TIM3->TCR = 0b10;	// reset timer
	LPC_TIM3->PR = SystemCoreClock/1000000; // microsecond steps
	LPC_TIM3->TCR = 0b01; // start timer

	for(int i =0; i<100; i++){
		toggleLed4();
		bits = bit_count(number);
		if(bits != 7){
			while(1);		
		}
	}

	*output = LPC_TIM3->TC; // read timer
	LPC_TIM3->TCR = 0b10; // reset and stop timer
	LPC_GPIO1->FIODIR |= 0b101101 << 18;
	LPC_GPIO1->FIOSET |= 0b101101 << 18;

	while(1);
}
