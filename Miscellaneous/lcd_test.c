#include<lpc17xx.h>

#include "Timer.h"
#include "LCD.h"
#include "PLL.h"

int i=0,j=0;
#define mes1 "Message 1"	
#define mes2 "Message 2"
#define mes3 "Message 3"
#define mes4 "Message 4"
#define mes5 "Message 5"
#define mes6 "Message 6"


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
