
/**
* @file     
* @brief    
* @version  
* @author   
* @date     2016-11-25
* @note     
*/

#if defined(_WINDOWS) || defined(_LINUX)

/*============================ INCLUDES ======================================*/

#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

/*============================ MACROS ========================================*/



/*============================ TYPES =========================================*/



/*============================ GLOBAL VARIABLES ==============================*/



/*============================ LOCAL VARIABLES ===============================*/



/*============================ IMPLEMENTATION ================================*/

char *unixtimestamp(void)
{
  static char buf[100];
  time_t t;
  struct tm *ptm;
  
  t = time(NULL);
  ptm = localtime(&t);
  sprintf(buf,"_%4d%02d%02d_%02d%02d%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, 
                                           ptm->tm_hour, ptm->tm_min, ptm->tm_sec);    
  return buf;                                               
}

// example: fullname("G:\src\main.c") --> filename(main)
void getfilename(char *fullname, char *filename)
{
  char *name_start, *name_end;
  int len;

  assert((NULL != fullname) && (NULL != filename));
  
  name_start = strrchr(fullname, '\\');
  if (NULL == name_start)
  {
    name_start = fullname;
  }
  else
  {
    name_start += 1;    
  }
  
  name_end = strrchr(fullname, '.');
  if (NULL == name_end)
  {
    name_end = fullname + strlen(fullname);
  }

  len = name_end - name_start;
  strncpy(filename, name_start, len);
  filename[len] = '\0';
}

#endif

