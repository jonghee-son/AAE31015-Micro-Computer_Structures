#ifndef   __DEFAULT_H__
#define   __DEFAULT_H__


#define DEBUG_TEST  1

#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <string.h>
#include    <math.h>

//#include    <intrinsics.h>

#include "stm32f4xx.h"

#define MHZ           *1000000l
#define KHZ           *1000l
#define HZ            *1l

#define abs32(x)        (x = (x > 0) ? x : (-1)*x)
#define SWAP16(A)	((((A << 8 ) & 0xFF00)) | ((A >> 8)& 0x00FF))
#define SWAP32(A)	((((A<<24)&0xFF000000)) | (((A<<8)&0x00FF0000)) | (((A>>8)&0x0000FF00)) | (((A>>24)&0x000000FF)))
#define HI_BYTE(x)      ( (x >> 8) & (0xFF) )
#define LO_BYTE(x)      ( (x >> 0) & (0xFF) )
#define MSB(x)          ( (x >> 8) & (0xFF) )
#define LSB(x)          ( (x >> 0) & (0xFF) )

typedef unsigned short const UC16;
typedef unsigned char const UC8;

typedef char int8;                        /**< The 8-bit signed data type. */
typedef volatile char vint8;              /**< The volatile 8-bit signed data type. */                                           
typedef unsigned char uint8;              /**< The 8-bit unsigned data type. */                                           
typedef volatile unsigned char vuint8;    /**< The volatile 8-bit unsigned data type. */                                           
typedef short int16;                      /**< The 16-bit signed data type. */                                           
typedef volatile short vint16;            /**< The volatile 16-bit signed data type. */                                           
typedef unsigned short uint16;            /**< The 16-bit unsigned data type. */                                           
typedef volatile unsigned short vuint16;  /**< The volatile 16-bit unsigned data type. */                                           
typedef long int32;                       /**< The 32-bit signed data type. */                                           
typedef volatile long vint32;             /**< The volatile 32-bit signed data type. */                                           
typedef unsigned long uint32;             /**< The 32-bit unsigned data type. */                                           
typedef volatile unsigned long vuint32;   /**< The volatile 32-bit unsigned data type. */

typedef uint8 SOCKET;

typedef unsigned long	ulong;
typedef unsigned short	ushort;
typedef unsigned char	uchar;
typedef unsigned int    uint;

typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;

#ifndef true  
  #define true		        1
#endif

#ifndef false  
  #define false		        0
#endif

#ifndef TRUE  
  #define TRUE		        1
#endif

#ifndef FALSE  
  #define FALSE		        0
#endif

#ifndef NULL
  #define NULL (void *)0
#endif

#include "stm32f4xx_it.h"

#endif

