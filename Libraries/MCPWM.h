#ifndef MCPWM
#define MCPWM

extern void Match_MCPWM(int,int);
extern void MCPWM_Init(void);
extern void Limit_MCPWM(int,int);
extern void MCPWM_Start(void);

#define Start_Timer0_MCPWM (1<<0)
#define Edge_Aligned_Timer0_MCPWM ~(1<<1)
#define Center_Aligned_Timer0_MCPWM (1<<1)
#define Passive_Timer0 (1<<2)

#define Start_Timer1_MCPWM (1<<8)
#define Edge_Aligned_Timer1_MCPWM ~(1<<9)
#define Center_Aligned_Timer1_MCPWM (1<<9)
#define Passive_Timer1 (1<<10)

#define Start_Timer2_MCPWM (1<<16)
#define Edge_Aligned_Timer2_MCPWM ~(1<<17)
#define Center_Aligned_Timer2_MCPWM (1<<17)
#define Passive_Timer2 (1<<18)

#define Start_Timer_MCPWM (1<<0)|(1<<8|(1<<16))
#define Edge_Aligned_Timer_MCPWM ((1<<1)|(1<<9)|(1<<17))
#define Center_Aligned_Timer_MCPWM ((1<<1)|(1<<9)|(1<<17))
#define Passive_Timer ((1<<2)|(1<<10)|(1<<18))

#endif
