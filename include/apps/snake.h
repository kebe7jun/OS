/*************************************************************************
	> File Name: include/apps/snake.h
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月17日 星期四 18时19分48秒
 ************************************************************************/

#ifndef _SNAKE_H
#define _SNAKE_H

typedef struct snake
{
	int x;
	int y;
	struct snake* next;
}Snake;

#define LEFT_KEY 75
#define UP_KEY 72
#define RIGHT_KEY 77
#define DOWN_KEY 80
#define ESC_KEY 1

int main_snake(char **option);

#endif
