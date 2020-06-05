#include<lpc17xx.h>

#include "PLL.h"
#include "LCD.h"
#include "DMA.h"
#include "Timer.h"
#include "Buzzer.h"
#include "RAM_Alternate.h"
#include "Interrupt_Test.h"

//====================================== DECLARATIONS ============================================

uint32_t Error=0x00000000;
#define message "Hello Ankit"

#define CCLK_Value	100
#define PreScalarValue 99999

//================================================================================================

//====================================== MAIN FUNCTION ===========================================
int main()
{
	PLL_Init(CCLK_Value);
	Timer_Init(PreScalarValue);
	LCD_Init();
	Buzzer_Init();
	LCD_Display(1,"POST Start");
	RAM_Check();
	Interrupt_Enable();
	Interrupt_Check();
	DMATest();
}
//====================================== END OF MAIN FUNCTION======================================
