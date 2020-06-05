#include<lpc17xx.h>

#include "LCD.h"
#include "RAM_Alternate.h"
#include "Buzzer.h"
#include "Timer.h"


#define Test_String1 "AAAAAAAA"
#define Test_String2 "55555555"
#define RAM_Start 0x10000280
#define RAM_End   0x10007FFF

int Error_Location;
int Error_Count=0;

void Display_Error_Location(void)
{
	LCD_Display(1,"Error location");
	LCD_Display_Num(2,Error_Location);
	Delay(2000);
	return;
}

void Write_Data(char *Location,char Test_String[])
{
	int count;
	for(count=0;count<8;count++)
	{
		*Location=Test_String[count];
		Location++;
	}
	return;
}

void Check_Data(char *Location,char Test_String[])
{
	int count;
	for(count=0;count<8;count++)
	{
		if(*Location!=Test_String[count])
		{
			Error_Count++;
			Error_Location=(int)Location;
			Display_Error_Location();
		}
		else
			;
		*Location=0x00;
		Location++;
	}
	return;
}

void RAM_Check(void)
{
	char *Check_Value;
	
	for(	Check_Value=(char *)RAM_Start	;	(Check_Value+7)<(char *)RAM_End	;	Check_Value=Check_Value+7	)
		{
			Write_Data(Check_Value,Test_String1);
			Check_Data(Check_Value,Test_String1);
		}
	
	if(Error_Count!=0)
		goto Error;
	
	for(	Check_Value=(char *)RAM_Start	;	(Check_Value+7)<(char *)RAM_End	;	Check_Value=Check_Value+7	)
		{
			Write_Data(Check_Value,Test_String2);
			Check_Data(Check_Value,Test_String2);
		}
		
		Error:	if(Error_Count>0)
		{
			LCD_Display(1,"RAM Faulty");
			Buzzer_Sound(2);
			Delay(1000);
		}
		else
			LCD_Display(1,"RAM OK");
		
		return;
}
