#include<lpc17xx.h>

#include "PLL.h"
#include "Timer.h"
#include "Buzzer.h"
#include "LCD.h"
#include "Interrupt_Test.h"

int main()
{
PLL_Init(100);
Timer_Init(99999);
LCD_Init();
LCD_Display(1,"Check start");
//Buzzer_Init();
Interrupt();
Interrupt_Check();
}
