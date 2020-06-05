 #ifndef LCD
 #define LCD 1
 #define RS 24
 #define RW 23
 #define EN 22
 #define d4 4
 #define d5 5
 #define d6 6
 #define d7 7
 #define dset LPC_GPIO2->FIOSET
 #define dclr LPC_GPIO2->FIOCLR
 #define clear "                "
 #define AUTOBAUD_Message "Config AutoBaud"
 
 #define LCD_DELAY_VALUE 999999
 extern void LCD_Convert(unsigned char g);
 extern void LCD_CMD(unsigned char c);
 extern void LCD_Init(void);
 extern void LCD_DATA(unsigned char v);
 extern void LCD_Clear(int line);
 extern void LCD_Display(int line, char a[]);
 extern void display2_LCD(char c[]);
 extern void LCD_Display_Num(int line,int x);
 extern void LCD_Display_Char_Position(unsigned char Position, unsigned char v[]);
 extern void LCD_Display_Character_Position(unsigned char Position, unsigned char v);
 extern void LCD_Display_Number_Position(unsigned char Position,int Number);
 extern void LCD_Delay(int Delay_Value);
 extern void LCD_display2(int a);
 #endif
