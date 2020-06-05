#include<lpc17xx.h>

#include "DMA.h"
#include "PLL.h"
#include "Buzzer.h"
#include "Timer.h"
#include "LCD.h"

#define CCLK_Value	100
#define PreScalarValue 99999
int main()
{
	PLL_Init(CCLK_Value);
	Timer_Init(PreScalarValue);
	LCD_Init();
	Buzzer_Init();
	DMATest();
}
