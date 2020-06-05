#include<lpc17xx.h>
#include "Timer.h"
#include "UART_AutoBaud.h"
#include "PLL.h"
#include "LCD.h"


#define DELAY_VALUE 1000
#define PRESCALAR_VALUE 99999
#define CCLK_VALUE 100 // In MHz

//========================================== MAIN FUNCTION ========================================

int main()
{
	int Loop_Count=0;
	char Test=0x00;	
	char message1[]=("Number: ");
	char message2[]=("Character: ");
  PLL_Init(CCLK_VALUE); 														// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE); 											// Initializing the timer with pre-defined pre-scalar values
	LCD_Init();																				// Initialize the LCD
	Delay(DELAY_VALUE);																
	LCD_Display(1,message1);
	LCD_Display(2,message2);
 	UART_Initialize(); 																// Initialize UART with AutoBaud
	Delay(DELAY_VALUE);
	UART0_SendString("Hi Ankit\r\n");
	Delay(DELAY_VALUE);
	UART0_SendString("Transmission Begins\r\n");	
	while(1)
	{	
			Loop_Count=0;																	// Resetting the Loop count
			Test=0x00;																		// Reset the hex value 
			LCD_Display(1,message1);
			LCD_Display(2,message2);
			while(Loop_Count<256)
			{
							UART0_TxNum(Loop_Count);
							LCD_Display_Number_Position(0x88,Loop_Count);
							Loop_Count++;
							UART0_SendString("\t");		
							LCD_Display_Character_Position(0xCA,Test);
							UART0_TxChar(Test);
							Test++;
							UART0_SendString("\r\n");		
							Delay(DELAY_VALUE);// Delay between consecutive loops
			}
	}
}
//======================================== END OF MAIN FUNCTION ===================================
