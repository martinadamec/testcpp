#include "bitCount.h"
#include "cmsis.h"

// Sigs for SIED
static const char IDB0 = 0;
static const char IDB1 = 1;
static const char IDB2 = 2;
static const char IDB3 = 3;

int bit_count(long x)
{

	volatile char X = 0;

	if(X!=IDB0){
		Sigerror();
	}

        int n = 0;

	

        if (x) {
		
//-------------------------------------------------
		do{
			
			X=IDB1;
			if(X != IDB1){
				Sigerror();
			}
			
              		n++;

			X = IDB2;
			
//-------------------------------------------------
        	}while( (X!=IDB2) || (0 != (x = x&(x-1))) );
//-------------------------------------------------
		if(X!=IDB2){
			Sigerror();
		}
	}
	X = IDB3;
	
	if(X!=IDB3){
		Sigerror();
	}

        return n;
}

void Sigerror(){
	LPC_GPIO1->FIODIR |= 0b101101<<18;
	LPC_GPIO1->FIOCLR = 0b101101<<18;
	LPC_GPIO1->FIOSET |= 0b000101<<18;
	while(1);
}
