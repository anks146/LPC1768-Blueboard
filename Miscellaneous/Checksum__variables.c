#include<lpc17xx.h>
#include "UART_AutoBaud.h"
#include "LCD.h"
#include "Timer.h"
#include "PLL.h"

#define Message_Checksum "Checksum is: "
#define Final_Checksum_Value "Final Checksum:"
#define FLASH_Start 0x00000000
#define FLASH_End 0x00000FFF
#define CHECKSUM_Address main

//======================================== MAIN FUNCTION ================================================

int main()
{
		int p=FLASH_Start,count=0;
		int Checksum;
		int *Pointer,*Final_Pointer;
		Pointer=(int *)FLASH_Start;
		Final_Pointer=(int *)CHECKSUM_Address;
		PLL_Init(12);																// Initialize the PLL for CPU Clock Frequency
		Timer_Init(11999);													// Initializing the timer with pre-defined pre-scalar values
		LCD_Init();																	// Initialize the LCD
		LCD_Display(1,Message_Checksum);

		UART_Initialize();													// Initialize UART with AutoBaud
		UART0_SendString("\r\nThe checksum are calculated for addresses from ");
		UART0_TxNum(FLASH_Start);										// Transmitting the start address for checksum (In integer)
		UART0_SendString(" till ");
		UART0_TxNum(FLASH_End);											// Transmitting the end address for checksum (In integer)
		Checksum=0;

			while(p<=FLASH_End) 
				{
					Checksum=(	Checksum	+	(*Pointer)	);// Calculating checksum
					Pointer++;														// Incrementing pointer to next address
					p=(int)Pointer;
				}
		
		UART0_SendString("\r\nThe checksum value is ");
		UART0_TxNum(Checksum); 											// Transmitting the checksum value
		LCD_Display_Num(2,Checksum);
		UART0_SendString("\r\nChecksum value is in FLASH memory at location - ");
		UART0_TxNum((int)CHECKSUM_Address); 				// Transmitting the address where checksum is stored(In integers)
		UART0_SendString(" for future use.\r\n");
}
//======================================== END OF MAIN FUNCTION =========================================
