#include "LPC17xx.h"

#define ENABLE_I2C (1<<6)
#define START_FLAG (1<<5)
#define STOP_FLAG  (1<<4)
#define ACKNWLEDGE (1<<2)
#define I2C_INTERRUPT (1<<3)

#define DISABLE_I2C (1<<6)
#define CLEAR_START_FLAG (1<<5)
#define CLEAR_ACKNWLEDGE (1<<2)
#define CLEAR_I2C_INTERRUPT (1<<3)

#define STATUS 
#define DATA
