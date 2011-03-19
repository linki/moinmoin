// http://markuskimius.wikidot.com/programming:tut:autotools:2

#include "config.h"
 
#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_SYS_TIME_H
#include <sys/time.h>
#else
#include <time.h>
#endif
 
int main(int argc, const char **argv)
{
   double sec;
   
   #ifdef HAVE_GETTIMEOFDAY
      struct timeval tv;

      gettimeofday(&tv, NULL);
      sec = tv.tv_sec;
      sec += tv.tv_usec / 1000000.0;
   #else
      sec = time(NULL);
   #endif
   
   printf("%f\n", sec);
 
   return EXIT_SUCCESS;
}
