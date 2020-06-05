#ifndef Timer
#define Timer 1
extern void Timer_Init(int);
extern void Delay(int);
extern void Start_Timer(void);
extern void Stop_Timer(void);
extern void Reset_Timer(void);
extern void Timer_Interrupt(int,int);
extern void Timer_Interrupt_Reset(int);

#endif
