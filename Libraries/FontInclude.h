#ifndef   __DEFFONT_H__
#define   __DEFFONT_H__

#include "Default.h"

typedef struct tFont
{    
  const unsigned char *table;
  uint16_t Width;
  uint16_t Height;
  uint16_t nData;
}gl_sFONT;

#include "Gulim7_6x10_ASCII.h"
#include "Gulim8_8x12_ASCII.h"
#include "Gulim10_8x16_ASCII.h"
#include "Gulim20_16x34_ASCII.h"
#include "Gulim28_24x48_ASCII.h"

#endif

