/*************************************************************************
	> File Name: apps/showTime.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 11时38分09秒
 ************************************************************************/

#include "stdio.h"
#include "time.h"
#include "apps/showTime.h"

int main_show_time()
{
	time_t t = time(NULL);
	int hour, minute, second;
	second = t%60;
	minute = t%3600/60;
	hour = t%(3600*24)/3600;
	printf("%d : %d : %d\n", hour, minute, second);
    return RUN_SUCCESS;
}
