/*************************************************************************
	> File Name: conio.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月15日 星期二 17时15分56秒
 ************************************************************************/

#include "conio.h"
#include "stdio.h"

static char keycode = -1;

//The callback function when user pressed a key.
void onGetKeyFunction(char keycode1)
{
	keycode = keycode1;
}
int getch()
{
	char keycode1;
	// printf("onGetKeyFunction:%d\n", &onGetKeyFunction);
    registerListenKey(&onGetKeyFunction);       //Register the callback function.
    while(keycode == -1);       //Wait for user press key.
    keycode1 = keycode;
    keycode = -1;
    return keycode1;
}
int getchInStep(uint32_t step)
{
	char keycode1;
	// printf("onGetKeyFunction:%d\n", &onGetKeyFunction);
    registerListenKey(&onGetKeyFunction);
    while(step--);       //Wait for user press key in steps.
    keycode1 = keycode;
    keycode = -1;
    return keycode1;
}