#include<lpc17xx.h>
#include "Timer.h"
#include "UART.h"
#include "PLL.h"
#include "LCD.h"

//=================================== GLOBAL VARIABLES =======================================
char Recieved_Data[Size];
int Reciver_Counter=0;
//============================================================================================
//========================================= LOCAL FUNCTIONS ==================================
void Clear_Recieved_Data(void)
{      
	int Counter=0;
	char Clear_Array[]=(" ");
       while(Counter<Reciver_Counter)
			  {
					Recieved_Data[Counter]=Clear_Array[0];
					Counter++;
			  }			
}
//============================================================================================

//==================================== UART INTERRUPT HANDLER ================================
void UART0_IRQHandler(void)
{
char IIRval;																					// For identifing the source of interrupt
char mes2[]=("AUTO BAUD COMPLETE");
char mes3[]=("AUTO BAUD INCOMPLETE");
char mes4[]=("Data Recieved");
IIRval=LPC_UART0->IIR;
//		lcddisplay(1,mes5);
			if( ((IIRval>>1)&0x07) == 0x02) 								// If receved data is available
		{
			
			Recieved_Data[Reciver_Counter]=LPC_UART0->RBR;	// Store the received data and resetting the interrupt flag
			Reciver_Counter++;															// Increment the total number of received character


			if(Reciver_Counter==Size)
			Reciver_Counter=0;
			
		LCD_Display(1,mes4);
		}

		else if( ((IIRval>>8)&0x01)==0x01) 								// If Auto baud successful
		LPC_UART0->ACR|=(1<<8);														// Clear  Interrupt
		
		else if( ((IIRval>>9)&0x01)==0x01) 								// If Auto baud timeout
		LPC_UART0->ACR|=(1<<9);	          								// Clear interrupt
}
//============================================================================================
//======================================== MAIN FUNCTION =====================================
int main()
{	
  char mes1[]=("Received Data");
	int Loop_Count=0;
  PLL_Init(12);																				// Initialize the PLL for CPU Clock Frequency
	Timer_Init(2);																			// Initialize the timer with pre-defined pre-scalar values
	LCD_Init();																					// Initialize the LCD
	UART_Initialize(9600);															// Initialize UART for 9600 Baudrate
	NVIC_EnableIRQ(UART0_IRQn);													// Enable UART0 interrupt
	Delay(1);
	UART0_SendString("\r\nHi Ankit\r\n");
	Delay(1);
	LCD_Display(1,mes1);
	while(1)
	{
					UART0_SendString("TRANSMISSION  ");
					UART0_TxNum(Loop_Count);
					UART0_SendString(" \r\n ");		
					Loop_Count++;																// Incrementing the Loop count for next transmission
		      Delay(10);
	}	
}
//====================================== END OF MAIN FUNCTION ================================
