/*************************************************************************
	> File Name: time.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月15日 星期二 15时54分43秒
 ************************************************************************/

#include "time.h"
static unsigned long int next = 1;
 
 int rand( void  ) // RAND_MAX assumed to be 32767
 {
         next = next * 1103515245 + 12345;
         return (unsigned int)(next / 65536) % 32768;

 }
  
  void srand( unsigned int seed  )
  {
          next = seed;

  }

