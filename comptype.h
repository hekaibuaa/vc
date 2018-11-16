
#ifndef COMPTYPE_H
#define COMPTYPE_H

typedef enum
{
  FRAME_READY = 0,
  FRAME_HALF  = 1,
  FRAME_EMPTY = 2,
  FRAME_ERROR = 3
}SearchFrameStatusEnum;

typedef struct 
{   
  s32 year, month, day;
  s32 hour, min;    
  f64 sec;
  s32 isec, msec;
  bool valid;
}UtcStruct; 

#endif

