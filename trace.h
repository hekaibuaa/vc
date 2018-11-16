
/**
* @file     trace.h
* @brief    
* @version  
* @author   
* @date     2016-7-10
* @note     
*/

#ifndef TRACE_H
#define TRACE_H

#include "config.h"

#if ENABLE_TRACE

/*============================ INCLUDES ======================================*/



/*============================ MACROS ========================================*/

#define TEROR 0
#define TWARN 1
#define TNOTE 2
#define TINFO 3

#if defined(_WINDOWS) || defined(_LINUX)
#define tracefile  tracefile_
#define traceopen  traceopen_
#define traceclose traceclose_
#else 
#define tracefile(...)
#define traceopen(...)
#define traceclose(...)
#endif

#define tracelevel tracelevel_
#define trace      trace_
#define traceb     traceb_

/*============================ TYPES =========================================*/



/*============================ GLOBAL VARIABLES ==============================*/



/*============================ PROTOTYPES ====================================*/

#if defined(_WINDOWS) || defined(_LINUX)
extern void tracefile_(char *filename_input, char *filename_trace);
extern void traceopen_(const char *file);
extern void traceclose_(void);
#endif

extern void tracelevel_(int level);
extern void trace_(int level, const char *format, ...);
extern void traceb_(int level, const unsigned char *p, int n);

#else

/*============================ INCLUDES ======================================*/



/*============================ MACROS ========================================*/

#define tracefile(...)
#define traceopen(...)
#define traceclose(...)
#define tracelevel(...)
#define trace(...)
#define traceb(...)

/*============================ TYPES =========================================*/



/*============================ GLOBAL VARIABLES ==============================*/



/*============================ PROTOTYPES ====================================*/



#endif // #if ENABLE_TRACE

#endif // #ifndef TRACE_H

