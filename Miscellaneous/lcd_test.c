#include<lpc17xx.h>

#include "Timer.h"
#include "LCD.h"
#include "PLL.h"

int i=0,j=0;
#define mes1 "HI ANKIT"	
#define mes2 "HI AAYUSHI"
#define mes3 "HI PRAKHAR"
#define mes4 "HI PIZZA"
#define mes5 "HI SYMBIOSIS"
#define mes6 "HI McD"


//======================================== MAIN FUNCTION ==========================================
int main()
{
  PLL_Init(12);							// Initialize the PLL for CPU Clock Frequency
	Timer_Init(11999);				// Initialize the timer with pre-defined pre-scalar values
	LCD_Init();								// Initialize the LCD
	Delay(10);
  while(1)
  {
			LCD_Display(1,mes1);	// Displaying various messages on LCD
			Delay(1000);
			LCD_Display(2,mes2);
			Delay(1000);
			LCD_Display(2,mes3);
			Delay(1000);
			LCD_Display(1,mes5);
			Delay(1000);
			LCD_Display(1,mes6);
			Delay(1000);
			LCD_Display(2,mes4);
			Delay(1000);
	}
}
//======================================== END OF MAIN FUNCTION ===================================
