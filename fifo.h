/**
* @file     
* @brief    
* @version  
* @author   
* @date     2018-3-16
* @note     
*/

#ifndef FIFO_H
#define FIFO_H

/*============================ INCLUDES ======================================*/

#include "basetype.h"

/*============================ MACROS ========================================*/

/* calculate current read position in fifo when ReadPos update */
#define IDX_READPOS(ReadPos, FifoSize) ((ReadPos) % (FifoSize))

/*============================ TYPES =========================================*/

typedef struct
{
  u8   *buf;
  u16  size;
  vu16 count;
  u16  ReadPos;
  u16  WritePos;
  u16  error;
}FifoStruct;

/*============================ PROTOTYPES ====================================*/

extern void FifoInit(FifoStruct *fifo, u8 *buf, u16 size);
extern void FifoClear(FifoStruct *fifo);
extern u16  FifoLength(FifoStruct *fifo);
extern void FifoWriteIn(FifoStruct *fifo, const u8 *buf, u16 len);
extern void FifoReadOut(FifoStruct *fifo, u8 *buf, u16 len);
extern void FifoUpdateReadPos(FifoStruct *fifo, u16 inc);
extern bool IsFifoEmpty(FifoStruct *fifo);

#endif


