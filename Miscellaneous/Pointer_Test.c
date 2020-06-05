#include<lpc17xx.h>
#include "UART_AutoBaud.h"
#include "LCD.h"
#include "Timer.h"
#include "PLL.h"

#define Message_Pointer_Begin "Pointer Initiate"
#define Message_Pointer "Pointer Successful"
#define Pointer_Address 0x10007F00

//====================================== MAIN FUNCTION =====================================
int main()
{
		int p=2047;
		int *Pointer,*Final_Pointer;									// Initializing pointer for integer datatype
		char *Pointer_Char;														// Initializing pointer for char datatype
		int i=0;
		char a[]=("Hello"); 
		Pointer=&p;																		// Assigning address to pointer
		Final_Pointer=(int *)Pointer_Address;					// Assigning address for final storage
		PLL_Init(12);																	// Initialize the PLL for CPU Clock Frequency
		Timer_Init(11999);														// Initialize the timer with pre-defined pre-scalar values
		LCD_Init();																		// Initialize the LCD
		LCD_Delay(5);																	// Displaying the delay specified on LCD
		LCD_Display(1,Message_Pointer_Begin);
		Delay(5000);
		Pointer_Char=&(a[0]);

			while(a[i]!='\0')
			{
				LCD_Display_Num(1,(int)Final_Pointer);
				LCD_Display_Num(2,i);
				*Final_Pointer=a[i];
				Final_Pointer++;
				i++;
				Delay(900);
			}
		LCD_Display(1,Message_Pointer);
		LCD_Display_Num(2,(int)Final_Pointer);		
}
//=================================== END OF MAIN FUNCTION =================================
