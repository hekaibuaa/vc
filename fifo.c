
/**
* @file     
* @brief    
* @version  
* @author   
* @date     2018-3-16
* @note     
*/

/*============================ INCLUDES ======================================*/

#include "basetype.h"

#include "fifo.h"

//#include "os.h"

#include <stddef.h>
#include <string.h>

/*============================ MACROS ========================================*/

#define ENABLE_MEMCPY (1)

#define CPU_SR_ALLOC(...)
#define CPU_CRITICAL_ENTER(...)
#define CPU_CRITICAL_EXIT()

/*============================ IMPLEMENTATION ================================*/

void FifoInit(FifoStruct *fifo, u8 *buf, u16 size)
{ 
  fifo->buf      = buf;
  fifo->size     = size;
  FifoClear(fifo);
}

void FifoClear(FifoStruct *fifo)
{
  fifo->count    = 0;
  fifo->ReadPos  = 0;
  fifo->WritePos = 0;
  fifo->error    = 0;
}

u16 FifoLength(FifoStruct *fifo)
{
  return fifo->count;
}

void FifoWriteIn(FifoStruct *fifo, const u8 *buf, u16 len)
{
  if ((NULL == fifo) || (NULL == buf) || (0 == len) || (len + fifo->count > fifo->size))
  {
    fifo->error++;
    
    return;  
  }

#if ENABLE_MEMCPY

  u16 remains = fifo->size - fifo->WritePos;

  if (len <= remains)
  {
    memcpy(fifo->buf + fifo->WritePos, buf, len);
  }
  else
  {
    memcpy(fifo->buf + fifo->WritePos, buf, remains);
    memcpy(fifo->buf, buf + remains, len - remains);
  }

  CPU_SR_ALLOC();
  CPU_CRITICAL_ENTER();
  fifo->WritePos = (fifo->WritePos + len) % fifo->size;
  fifo->count += len;
  CPU_CRITICAL_EXIT();
  
#else

  for (u16 i = 0; i < len; i++)
  {
    fifo->buf[fifo->WritePos++] = buf[i];
    fifo->WritePos %= fifo->size;
  }
  fifo->count += len;
  
#endif
}

void FifoReadOut(FifoStruct *fifo, u8 *buf, u16 len)
{
  if ((NULL == fifo) || (NULL == buf) || (0 == len) || (len > fifo->count))
  {
    fifo->error++;
    
    return;  
  }

#if ENABLE_MEMCPY

  u16 ReadPos = fifo->ReadPos;
  u16 remains = fifo->size - ReadPos;
    
  if (len <= remains)
  {
    memcpy(buf, fifo->buf + ReadPos, len);
  }
  else
  {
    memcpy(buf, fifo->buf + ReadPos, remains);
    memcpy(buf + remains, fifo->buf, len - remains);
  }
  
#else

  u16 i, ReadPos = fifo->ReadPos;

  for (i = 0; i < len; i++)
  {
    buf[i] = fifo->buf[ReadPos++];
    ReadPos %= fifo->size;
  }

#endif
}

void FifoUpdateReadPos(FifoStruct *fifo, u16 inc)
{
  if (inc > fifo->count)
  {  
    return;
  } 

  CPU_SR_ALLOC();
  CPU_CRITICAL_ENTER();  
  fifo->ReadPos = (fifo->ReadPos + inc) % fifo->size;
  fifo->count -= inc;
  CPU_CRITICAL_EXIT();
}

bool IsFifoEmpty(FifoStruct *fifo)
{
  return ((fifo->ReadPos == fifo->WritePos) && (0 == fifo->count)) ? TRUE : FALSE;
}



