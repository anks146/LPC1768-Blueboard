#include<lpc17xx.h>
#include "LCD.h"
#include "PLL.h"
#include "Timer.h"

#define Message_Checksum "Checksum is: "
#define Final_Checksum_Value "Final Checksum:"
#define FLASH_Start 0x00000000
#define FLASH_End 0x0007FFFF
#define CHECKSUM_Address 0x2007CFC0

//=======================================================================================================
#define Start_Section_Number 5
#define End_Section_Number 5
#define RAM_Location CHECKSUM_Address
#define FLASH_Location 0x0003FF50
#define BYTES 256
#define FREQ 100000

int Ready_Sector[]={50,Start_Section_Number,End_Section_Number};
int Write_Flash[]={51,FLASH_Location,RAM_Location,BYTES,FREQ};

#define IAP_Location 0x1FFF1FF1
unsigned long command[5];
unsigned long output[5];

typedef void (*IAP)(unsigned int [],unsigned int[]);
IAP iap_entry;
iap_entry=(IAP)IAP_Location;

//========================================= MAIN FUNCTION ================================================

int main()
{
		int p=FLASH_Start;
		int Checksum;
		int *Pointer,*Final_Pointer;
		Pointer=(int *)FLASH_Start;
		Final_Pointer=(int *)CHECKSUM_Address;
		PLL_Init(12);																// Initialize the PLL for CPU Clock Frequency
		Timer_Init(11999);													// Initializing the timer with pre-defined pre-scalar values
		LCD_Init();																	// Initialize the LCD
		LCD_Display(1,Message_Checksum);
		Checksum=0;
		command[]={50,Start_Section_Number,End_Section_Number};
		iap_entry(command,&output);
			while(p<=FLASH_End) 
				{
					Checksum=(	Checksum	+	(*Pointer)	);// Calculating checksum
					Pointer++;														// Incrementing pointer to next address
					p=(int)Pointer;
				}
		
		LCD_Display_Num(2,Checksum);
		*Final_Pointer=Checksum;
}
//======================================== END OF MAIN FUNCTION =========================================
