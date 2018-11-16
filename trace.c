
/**
* @file     trace.c
* @brief    
* @version  
* @author   
* @date     2016-6-19
* @note     
*/

/*============================ INCLUDES ======================================*/
 
#include "config.h"

#if ENABLE_TRACE

#include "trace.h"

#include <assert.h>
#include <stdarg.h> 
 
/*============================ MACROS ========================================*/

#if defined(_WINDOWS) || defined(_LINUX)
#define DBG_MODE_WINFILE 1
#endif

#ifdef _STM
#define DBG_MODE_JTAGRTT 1
#define DBG_MODE_STMUART 1
#define DBG_MODE_STMUSB  0
#define DBG_MODE_TCPNET  0
#endif

/*------- _WINDOWS || _LINUX -------*/

#if defined(_WINDOWS) || defined(_LINUX)

#if DBG_MODE_WINFILE
#include "libpc.h"
#include <stdio.h>     
#include <string.h>
static FILE *fp_trace = NULL;   
#endif

#define TRACE_BUF_LENGTH (1024 * 1024 * 10) // 10M bytes

#endif // #if defined(_WINDOWS) || defined(_LINUX)

/*------------- _STM ---------------*/

#ifdef _STM 

#include "stmtype.h"

#if DBG_MODE_JTAGRTT
#include "SEGGER_RTT.h"
#define RTT_TERMINAL 0
#endif

#if DBG_MODE_STMUART
#include "drv_debug.h"           
#endif

#if DBG_MODE_STMUSB

#endif 

#if DBG_MODE_TCPNET

#endif

#define TRACE_BUF_LENGTH (1024 * 4) // 4K bytes 

#endif // #ifdef _STM 

/*============================ TYPES =========================================*/
 
 
 
/*============================ GLOBAL VARIABLES ==============================*/
 

 
/*============================ LOCAL VARIABLES ===============================*/
 
static char tracebuf[TRACE_BUF_LENGTH] = {0}; 
static int level_trace = 0;        
 
/*============================ IMPLEMENTATION ================================*/

#if defined(_WINDOWS) || defined(_LINUX)

// example: filename_input("G:\src\main.c") --> filename_trace(trace_main.txt)
// note: if filename_input[] is empty, you need input filename by screen
void tracefile_(char *filename_input, char *filename_trace)
{
  char filename_cut[200];

  if (0 == strlen(filename_input))
  {
    printf("please input file name:\r\n");
    scanf("%s", filename_input);
  }

  getfilename(filename_input, filename_cut);
	
  //sprintf(filename_trace, "trace_%s%s.txt", filename_cut, unixtimestamp()); // add timestamp to file tail
  sprintf(filename_trace, "trace_%s.txt", filename_cut); // not add timestamp
  printf("trace file is %s\r\n", filename_trace);
}

void traceopen_(const char *file)
{    
#if DBG_MODE_WINFILE 
  if (!*file || !(fp_trace = fopen(file,"w"))) 
  {
    fp_trace = stderr;
  }    
#endif    
}

void traceclose_(void)
{
#if DBG_MODE_WINFILE
  if (fp_trace && (stderr != fp_trace)) 
  {
    fclose(fp_trace);
  }
  
  fp_trace = NULL;
#endif    
}

#endif // #if defined(_WINDOWS) || defined(_LINUX)

void tracelevel_(int level)
{
  level_trace = level;
}

void trace_(int level, const char *format, ...)
{
  va_list ap;
  int len = 0;

  if (level > level_trace) 
  {
    return;    
  }
  
  va_start(ap, format); 
  len = vsprintf(tracebuf, format, ap); 
  va_end(ap);

#if defined(_WINDOWS) || defined(_LINUX)

#if DBG_MODE_WINFILE
  assert(NULL != fp_trace);
  fprintf(fp_trace, "%s", tracebuf);
  fflush(fp_trace);
#endif
#if DBG_MODE_JTAGRTT

#endif // #if defined(_WINDOWS) || defined(_LINUX)

#ifdef _STM

  SEGGER_RTT_printf(RTT_TERMINAL, "%s", tracebuf);
#endif

#if DBG_MODE_STMUART
  if (NULL != g_DebugUartCfg.pSendData)
  {
    g_DebugUartCfg.pSendData((u8 *)tracebuf, (u16)len);
  }  
#endif  

#if DBG_MODE_STMUSB

#endif

#if DBG_MODE_TCPNET

#endif  

#endif // #ifdef _STM
}

void traceb_(int level, const unsigned char *p, int n)
{
  int i, len = 0;
    
  if (level > level_trace) 
  {
    return;    
  }
  
  for (i = 0; i < n; i++) 
  {
    len += sprintf(tracebuf + len, "%02X,", *p++);
    if ((len + 10) > TRACE_BUF_LENGTH) // too many data, discard 
    {
      break;
    }
  }
  len += sprintf(tracebuf + len,"\r\n");

#if defined(_WINDOWS) || defined(_LINUX)

#if DBG_MODE_WINFILE  
  assert(NULL != fp_trace);
  fprintf(fp_trace, "%s", tracebuf);
  fflush(fp_trace);
#endif

#endif // #if defined(_WINDOWS) || defined(_LINUX)

#ifdef _STM

#if DBG_MODE_JTAGRTT
  SEGGER_RTT_printf(RTT_TERMINAL,"%s",tracebuf); 
#endif

#if DBG_MODE_STMUART
  if (NULL != g_DebugUartCfg.pSendData)
  {
    g_DebugUartCfg.pSendData((u8 *)tracebuf,(u16)len);
  }
#endif

#if DBG_MODE_STMUSB

#endif

#if DBG_MODE_TCPNET

#endif

#endif // #ifdef _STM
}

#endif // #if ENABLE_TRACE

