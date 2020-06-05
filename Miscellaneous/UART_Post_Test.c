#include <lpc17xx.h>
#include "Timer.h"
#include "PLL.h"
#include "LCD.h"
#include "UART_Post.h"
#include "Buzzer.h"

int main()
{
	PLL_Init(100);
	Timer_Init(99999);
	LCD_Init();
	Buzzer_Init();
	UART0_POST();
}
