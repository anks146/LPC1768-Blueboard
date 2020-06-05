#ifndef	DMA
#define DMA

#define TransferSize 0
#define SourceBurst 12
#define DestBurst 15
#define SourceWidth 18
#define DestWidth 18
#define SourceIncrement 26
#define DestIncrement 27

extern void DMAChannelConfig_MTM(int TotalSize,int Burst,int Channel,int Source,int Destination,int DataWidth);
extern void DMAChannelEnable(int Channel);
extern void DMAChannelDisable(int Channel);
extern void DMACheckChannelEnabled(int Channel);
extern void DMAEnable(void);
extern void DMADisable(void);
extern void DMACheck(int size, int src ,int dest);
extern void DMATest(void);
#endif
