#include<lpc17xx.h>

#include "Timer.h"
#include "DAC.h"
#include "PLL.h"
#include "Waveform.h"

#define Size 360
#define Step_Size_Value 1
#define Delay_Value 10000
#define PreScalar_Value 0
#define CCLK_Value 100
#define Match_Register 0

//================================ MAIN FUNCTION ======================================

int main()
{	
	PLL_Init(CCLK_Value);                        // Initialize the PLL for CPU Clock Frequency
	DAC_Init();                                  // Initialize DAC
	Timer_Init(PreScalar_Value);                 // Initialize the timer with pre-defined pre-scalar values
	Sin_Array(Size,Step_Size_Value);             // Storing sine values in an array
  Timer_Interrupt(Match_Register,Delay_Value); // Enable UART0 interrupt
	Start_Timer();      												 // Enable timer
	while(1)
		{
		//
		}
}

//================================ END OF MAIN FUNCTION ===============================
//=====================================================================================
void TIMER0_IRQHandler(void)
{
	LPC_TIM0->IR=0X0F;                           // Reset interrupt
	//Triangular_Wave(Size,Step_Size_Value);
	Sine_Wave(Size,Step_Size_Value);
	//Sawtooth_Wave(600,2);
	//Rectangular_Wave(1023);
}
//================================ END OF MAIN FUNCTION ===============================
