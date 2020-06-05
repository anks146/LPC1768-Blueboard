#include<lpc17xx.h>
#include "Timer.h"
#include "UART_AutoBaud.h"
#include "PLL.h"
#include "LCD.h"

#define DELAY_VALUE 300
#define PRESCALAR_VALUE 9999
#define CCLK_VALUE 100 // In MHz
#define BAUD_RATE 9600

//======================================== MAIN FUNCTION ===================================
int main()
{
	int Loop_Count=0;																// To count the number of	 loops executed
  LCD_Init();
	PLL_Init(CCLK_VALUE); 													// Initialize the PLL for CPU Clock Frequency
	Timer_Init(PRESCALAR_VALUE); 										// Initialize the timer with pre-defined pre-scalar values
 	UART_Initialize(); 										// Initialize UART for specific baud rate
	Delay(DELAY_VALUE);
	UART0_SendString("Hi Ankit\r\n");
	Delay(DELAY_VALUE);
	while(1)
	{
		UART0_SendString("TRANSMISSION  ");
		UART0_TxNum(Loop_Count);											// Transmit the loop count
		UART0_SendString("\r\n");		
		Loop_Count++;																	// Increment the loop count
		UART0_SendString("LASER ON\r\n");		
		Delay(DELAY_VALUE); // Delay between consecutive loops
		UART0_SendString("LASER OFF\r\n");		
		Delay(DELAY_VALUE); // Delay between consecutive loops
	}	
}
//======================================== END OF MAIN FUNCTION ============================
