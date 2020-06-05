#include<lpc17xx.h>

#include "PLL.h"
#include "Timer.h"
#include "LCD.h"
#include "RAM_Alternate.h"
#include "Buzzer.h"
#include "Interrupt_Test.h"

//====================================== MAIN FUNCTION ===========================================
int main()
{
	PLL_Init(100);
	Timer_Init(99999);
	LCD_Init();
	LCD_Display(1,"Check start");
	Buzzer_Init();
	RAM_Check();
}
//====================================== END OF MAIN FUNCTION======================================
