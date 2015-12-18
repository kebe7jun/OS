/*************************************************************************
	> File Name: libs/math.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 09时33分49秒
 ************************************************************************/

#include "math.h"


int pow(int x, int p)
{
	int t = x;
	if (p == 0)
	{
		return 1;
	}
	p--;
	while(p-- && p>-1)
	{
		x *= t;
	}
	return x;
}
int abs(int value)
{
	return value<0?-value:value;
}