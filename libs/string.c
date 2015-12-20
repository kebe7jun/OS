/*************************************************************************
	> File Name: libs/string.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 09时18分45秒
 ************************************************************************/


#include "string.h"
#include "math.h"

//To get the length of a string.
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

//Copy the second string to the first string.
void strcpy(char* to, char* from)
{
	char *to1 = to;
	while(*from)
	{
		*to1++ = *from++;
	}
	*to1++ = '\0';		//Append the \0 to the end of the str.
}

//Convert a string to a integer.
int convertStringToInt(char *str)
{
	int t = 0, p = 0;
	int len;
	len = strlen(str);
	while(len)
	{
		t+= (str[len-1]-'0')*pow(10, p++);	//
		len--;
	}
	return t;
}

//Cmp to str, if the two strs is the same, return 0.
int strcmp(char* str1, char *str2)
{
	int cmp = 0;
	int len = 0;
	while(*str1 && *str2)
	{
		cmp+=(*str1-*str2);
		str1++;
		str2++;
	}
	len = strlen(str1);
	while (len--)
	{
		cmp += *str1++;
	}
	len = strlen(str2);
	while (len--)
	{
		cmp -= *str2++;
	}
	return cmp;
}

//Split a str to str array wich given character.
char** split(char *str, char ch)
{
	char x[100][100];
	int len = strlen(str);
	int i = 0;
	int j = 0;
	for (i = 0; i<len; i++)
	{
		if (str[i] == ch)
		{
			str[i] = '\0';
		}
	}
	for (i = 0; i<len; )
	{
		while(!str[i++]);
		strcpy(x[j++], str+i-1);
		while(str[i++]);
	}
	x[j][0] = '\0';
	return x;
}