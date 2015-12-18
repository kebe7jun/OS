/*************************************************************************
	> File Name: include/string.h
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 09时16分34秒
 ************************************************************************/

#ifndef _INCLUDE/STRING_H
#define _INCLUDE/STRING_H
int strlen(char* str);
void strcpy(char* to, char* from);
int strcmp(char* str1, char *str2);
int convertStringToInt(char *str);
char **split(char *str, char ch);
#endif
