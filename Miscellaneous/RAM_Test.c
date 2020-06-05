#include<lpc17xx.h>

//#include "UART_AutoBaud.h"
#include "PLL.h"
#include "Timer.h"
#include "LCD.h"
#include "RAM.h"
#include "Buzzer.h"
#include "Interrupt_Test.h"

//====================================== MAIN FUNCTION ===========================================
int main()
{
	PLL_Init(100);
	//UART_Initialize();
	Timer_Init(99999);
	LCD_Init();
	LCD_Display(1,"Check start");
	Buzzer_Init();
	RAM_Check();
}
//====================================== END OF MAIN FUNCTION======================================
