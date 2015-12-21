/*************************************************************************
	> File Name: conio.h
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月15日 星期二 17时13分38秒
 ************************************************************************/

#ifndef _CONIO_H
#define _CONIO_H
#include "stdio.h"

//Get a key from keyboard, while user press.
int getch();

//Get a key from keyboard in step.
//
int getchInStep(uint32_t step);

#endif
