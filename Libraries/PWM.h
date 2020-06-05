#ifndef PWM
#define PWM

#define InterruptEnableCH0 (1<<0)
#define InterruptEnableCH1 (1<<3)
#define InterruptEnableCH2 (1<<6)
#define InterruptEnableCH3 (1<<9)
#define InterruptEnableCH4 (1<<12)
#define InterruptEnableCH5 (1<<15)
#define InterruptEnableCH6 (1<<18)
#define ResetEnableCH0 (1<<1)
#define ResetEnableCH1 (1<<4)
#define ResetEnableCH2 (1<<7)
#define ResetEnableCH3 (1<<10)
#define ResetEnableCH4 (1<<13)
#define ResetEnableCH5 (1<<16)
#define ResetEnableCH6 (1<<19)



#define SingleEdgeModeCH2	~(1<<2);	
#define SingleEdgeModeCH3	~(1<<3);
#define SingleEdgeModeCH4	~(1<<4);
#define SingleEdgeModeCH5	~(1<<5);
#define SingleEdgeModeCH6	~(1<<6);
#define DoubleEdgeModeCH2	(1<<2);
#define DoubleEdgeModeCH3	(1<<3);
#define DoubleEdgeModeCH4	(1<<4);
#define DoubleEdgeModeCH5	(1<<5);
#define DoubleEdgeModeCH6	(1<<6);

#define InterruptFlagCH0 1<<0
#define InterruptFlagCH1 1<<1
#define InterruptFlagCH2 1<<2
#define InterruptFlagCH3 1<<3
#define InterruptFlagCH4 1<<8
#define InterruptFlagCH5 1<<9
#define InterruptFlagCH6 1<<10

#define PWM_Counter_Enable 1<<0
#define PWM_Counter_Reset 1<<1
#define PWM_Enable_Bit 1<<3

#define EnableCH1	(1<<9)
#define EnableCH2	(1<<10)
#define EnableCH3	(1<<11)
#define EnableCH4	(1<<12)
#define EnableCH5	(1<<13)
#define EnableCH6	(1<<14)

extern void PWM_Init(int);
extern void PWM_Match(int,int);
extern void PWM_Enable(void);
#endif

