#include<lpc17xx.h>

#include "LCD.h"
#include "RAM.h"
#include "Buzzer.h"

#define RAM_Start 0x10000280
#define RAM_End 0x10007FFF

int Error_Count=0;

//==========================================================================================
//================================= Check Location =========================================
void Check_Location(int *Current_location)
{
		int Loop_Count=0;
	
		while(Loop_Count<32)
			{
				*Current_location=(1<<Loop_Count);
		
					if(	(		*Current_location		>>	Loop_Count)	==1)
						;
					else
						Error_Count++;
			
				Loop_Count++;
			}
}

//==========================================================================================
//================================= Check RAM Location =====================================

void Check_RAM_Locations(int * Location)
{
	int *Current_Location,temp_val;
	
		for(Current_Location=(int *) RAM_Start;Current_Location<=(int *)RAM_End;Current_Location++) // For all locations from start to end of RAM
		{
			
			if(Current_Location != Location) // If location under test is current location, skip
					{
						temp_val=*Current_Location; // Store value from location under test
						*Current_Location=0;

						if(*Current_Location==0)
							;
						else
							Error_Count++;
					}
			
			
			*Current_Location=temp_val; // Load the value originally stored in the location
			Current_Location++;
		}
}

//==========================================================================================
//====================================== RAM Check =========================================

void RAM_Check(void)
{
	int temp;
	int *Check_Counter;
	LCD_Display(1,"RAM TEST START");
	for(Check_Counter=(int *)RAM_Start;	Check_Counter<=(int *)RAM_End;	Check_Counter++) // For checking each memory location from start to end for RAM
	{
			if(	(	(int)Check_Counter	%1000	)	==0	)
			LCD_Display_Num(2,(int) Check_Counter);
			
			temp = *Check_Counter;												// Store value in the location under test
			Check_Location(Check_Counter);								// Check each bit of current RAM location
			Check_RAM_Locations(Check_Counter);						// Check other RAM locations
			*Check_Counter = temp;												// Load the value which was originally stored in the location.
	}
	
	if(Error_Count==0)
		LCD_Display(1,"RAM OK");
	else
	{
		LCD_Display(1,"RAM NOT OK");
		Buzzer_Sound(2);
		LCD_Display_Num(2,Error_Count);
	}
}
//===========================================================================================
