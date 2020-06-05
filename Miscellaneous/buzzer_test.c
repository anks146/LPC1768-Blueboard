#include<lpc17xx.h>
#include "PLL.h"
#include "Timer.h"
#define buzzer (1<<11)

//======================================== MAIN FUNCTION ===================================
int main()
{
	PLL_Init(100);						// Initialize the PLL for CPU Clock Frequency
	Timer_Init(99999);				// Initialize the timer with pre-defined pre-scalar values
	LPC_PINCON->PINSEL4=0;		// Initialize pin for Buzzer
	LPC_GPIO2->FIODIR|=buzzer;
	while(1)
	{
		LPC_GPIO2->FIOSET|=buzzer; 		// Toggle buzzer On and Off
		Delay(125);
		LPC_GPIO2->FIOCLR|=buzzer;
		Delay(250);
	}
}
//======================================== END OF MAIN FUNCTION ============================
