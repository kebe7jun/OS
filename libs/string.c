/*************************************************************************
	> File Name: libs/string.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 09时18分45秒
 ************************************************************************/


#include "string.h"
#include "math.h"


int strlen(char* str)
{
	int len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return len;
}
void strcpy(char* to, char* from)
{
	char *to1 = to;
	while(*from)
	{
		*to1++ = *from++;
	}
	*to1++ = '\0';
}

int convertStringToInt(char *str)
{
	int t = 0, p = 0;
	int len;
	len = strlen(str);
	while(len)
	{
		t+= (str[len-1]-'0')*pow(10, p++);
		len--;
	}
	return t;
}