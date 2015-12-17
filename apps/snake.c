/*************************************************************************
	> File Name: apps/snake.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月17日 星期四 18时21分44秒
 ************************************************************************/

#include "stdio.h"
#include "time.h"
#include "math.h"
#include "conio.h"
#include "apps/snake.h"

	
	
static Snake snake;
static Snake *head;
static uint32_t bodySize = 0;
static uint32_t startMem = 0xf00000;
static char nowX = 0;
static char nowY = 0;
static char foodX = 0;
static char foodY = 0;

Snake *newSnake()
{
	Snake *s;
	int p = startMem + bodySize*sizeof(Snake);
	if (p>=0xffffff)
	{
		p = startMem;
	}
	s = (Snake*)p;
	bodySize++;
	s->next = NULL;
	return s;
}

void newFood()
{
	int fx, fy;
	int valid = 1;
	Snake *s = snake.next;
	srand(time(NULL));
	while(1)
	{
		fx = abs(rand())%70;
		fy = abs(rand())%20;
		while(s)
		{
			if (fx == s->x && fy == s->y)
			{
				valid = 0;
			}
			s = s->next;
		}
		if (valid)
		{
			break;
		}
	}
	foodX = fx;
	foodY = fy;
}

void initSnake()
{
	Snake *s, *s1;
	s = newSnake();
	s->x = 30;
	s->y = 12;
	s1 = s;
	snake.next = s;
	s = newSnake();
	s->x = 31;
	s->y = 12;
	s1->next = s;
	s1 = s;
	s = newSnake();
	s->x = 32;
	s->y = 12;		//Head
	s1->next = s;
	head = s;
	nowX = 1;
	nowY = 0;
	newFood();
}

void printScreen()
{
	Snake *s = snake.next;
	console_clear();
	while(s)
	{
		putch_color_pos('*', rc_black, rc_white, s->x, s->y);
		s = s->next;
	}
	putch_color_pos('#', rc_black, rc_white, foodX, foodY);
	putch_color_pos(' ', rc_black, rc_white, 79, 24);
}

int moveSnake(char toX, char toY)
{
	int newX, newY;
	Snake *s;
	newX = head->x+toX;
	newY = head->y+toY;
	nowX = toX;
	nowY = toY;
	if (newX<0 || newY <0 || newX >=70 || newY >=20)
	{
		printf("End!\n");
		return 1;
	}
	s = newSnake();
	s->x = newX;
	s->y = newY;
	head->next = s;
	head = s;
	if (newX == foodX && newY == foodY)
	{
		newFood();
	}
	else
	{
		snake.next = snake.next->next;
	}
	printScreen();
	return 0;
}


void startGame()
{
	int key;
	int result;
	printScreen();
	while(1)
	{
		key = getchInStep(300000000);
		switch(key)
		{
			case LEFT_KEY:
				if (!(nowX == 1 && nowY == 0))
				{
					result = moveSnake(-1, 0);
				}
				break;
			case RIGHT_KEY:
				if (!(nowX == -1 && nowY == 0))
				{
					result = moveSnake(1, 0);
				}
				break;
			case UP_KEY:
				if (!(nowX == 0 && nowY == 1))
				{
					result = moveSnake(0, -1);
				}
				break;
			case DOWN_KEY:
				if (!(nowX == 0 && nowY == -1))
				{
					result = moveSnake(0, 1);
				}
				break;
		}
		result = moveSnake(nowX, nowY);
		if (result)
		{
			break;
		}
	}
}

int main_snake()
{
	initSnake();
	printScreen();
	startGame();
	return 0;
}

