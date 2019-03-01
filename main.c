#include "msp.h"
#include <stdint.h>
#include "BSP.h"

void initBuzzerPin(){
	P2SEL0 &= ~0xf0;
	P2SEL1 &= ~0xf0;
	
	P2DIR |= 0xf0;
	
}

int main(){
	WDT_A->CTL = WDT_A_CTL_PW|WDT_A_CTL_HOLD;
	initBuzzerPin();
	BSP_Buzzer_Init((uint16_t) 0x00);
	BSP_Buzzer_Set((uint16_t) 0x200);
}
