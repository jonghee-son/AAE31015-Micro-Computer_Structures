#ifndef _FRAM_RTC_H_
#define _FRAM_RTC_H_
#include "Default.h"

#ifdef _FRAM_RTC_C_
	#define FRAM_RTC_EXT
#else
	#define FRAM_RTC_EXT extern
#endif

// FRAM OP-CODE
#define WREN  0x06
#define WRDI  0x04
#define RDSR  0x05
#define WRSR  0x01
#define READ  0x03
#define WRITE 0x02

FRAM_RTC_EXT void Fram_Init(void);
FRAM_RTC_EXT void Fram_Write(short addr,unsigned char data);
FRAM_RTC_EXT unsigned char Fram_Read(short addr);
FRAM_RTC_EXT void Fram_Status_Config(void);
#endif

