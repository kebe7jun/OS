/*************************************************************************
	> File Name: conio.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月15日 星期二 17时15分56秒
 ************************************************************************/

#include "conio.h"
#include "stdio.h"

static char keycode = -1;


void onGetKeyFunction(char keycode1)
{
	keycode = keycode1;
}
int getch()
{
	char keycode1;
    registerListenKey(&onGetKeyFunction);
    while(keycode == -1);
    keycode1 = keycode;
    keycode = -1;
    return keycode1;
}