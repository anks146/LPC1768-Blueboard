#ifndef UART
#define UART 1
#define Size 16
#define RDA 0x02
#define RLS 0x03
#define CTI 0x06


extern void UART_Initialize(int baud);
extern void UART0_TxChar(char ch);
extern void UART0_TxNum(int num);
extern void UART0_SendString(char *ch);
#endif
