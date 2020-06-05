#include<lpc17xx.h>
#include "Buzzer.h"
#include "Timer.h"
#include "PLL.h"
#include "LCD.h"

int main()
{
	int a=1;
	PLL_Init(100);						// Initialize the PLL for CPU Clock Frequency
	Timer_Init(99999);				// Initialize the timer with pre-defined pre-scalar values
	Buzzer_Init();
	LCD_Init();
	LCD_Display(1,"Start");
	Delay(1000);
	LCD_Display(1,"Count:");
	
	while(1)
	{
		LCD_Display_Num(2,a);
		Buzzer_Sound(a);
		Delay(2000);
		a=a+3;
		LCD_Display_Num(2,a);
	}
}	
