#include<lpc17xx.h>
#include "UART_AutoBaud.h"
#include "LCD.h"
#include "Timer.h"
#include "PLL.h"

#define Message_Pointer_Begin "Pointer Initiate"
#define Message_Pointer "Pointer Success"
#define Pointer_Address 0x00000360;

//=========================================== MAIN FUNCTION ============================================

int main()
{
	int p=54789;  												 // Random value assigned
	int *Pointer,*Final_Pointer;
	int a=214748; 										     // Random value assigned
	Pointer=&p;	 													 //Pointer assigned a variable v 
	Final_Pointer=(int *)Pointer_Address;  // Address for storing final value
	PLL_Init(100);                         // Initialize the PLL for CPU Clock Frequency
	Timer_Init(99999);                     // Initializing the timer with pre-defined pre-scalar values
	LCD_Init();                            // Initializing the LCD
	LCD_Delay(5);                          // Displaying for 5 seconds delay

	LCD_Display(1,Message_Pointer_Begin);
	LCD_Display_Num(2,(int)Pointer);       // Displaying address of predefined value
	Delay(5000);
	LCD_Display(1,Message_Pointer);
	*Final_Pointer=a;                      // Storing value at particular location
	LCD_Display_Num(2,(int)Final_Pointer); //Displaying the locating where value is stored
	LCD_Display(1,Message_Pointer);
}
//======================================== END OF MAIN FUNCTION ========================================
