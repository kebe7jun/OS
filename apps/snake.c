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
static int speed = 300000000;
static uint32_t score = 0;

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
	score += speed/100000000;
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
	int i;
	console_clear();
	while(s->next)
	{
		putch_color_pos('*', rc_black, rc_white, s->x, s->y);
		s = s->next;
	}
	putch_color_pos('@', rc_black, rc_white, s->x, s->y);
	putch_color_pos('#', rc_black, rc_green, foodX, foodY);

	for (i = 0; i < 20; ++i)
	{
		putch_color_pos('|', rc_black, rc_white, 70, i);	
	}

	for (i = 0; i < 70; ++i)
	{
		putch_color_pos('-', rc_black, rc_white, i, 20);	
	}

	putch_color_pos('\0', rc_black, rc_white, 70, 5);
	printf("Score: %d\n", score);
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
	s = snake.next;
	while(s)
	{
		if (newX == s->x && newY == s->y)
		{
			printf("End!\n");
			return 1;
		}
		s = s->next;
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
		key = getchInStep(speed);
		if (key == ESC_KEY)
		{
			printf("User End.\n");
			break;
		}
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

// int checkOption(char** option)
// {
// 	char s;
// 	if (strcmp(option[1], "-s"))
// 	{
// 		s = option[2][0];
// 		switch(s)
// 		{
// 			case '1':
// 				speed = 700000000;
// 				break;
// 			case '2':
// 				speed = 500000000;
// 				break;
// 			case '3':
// 				speed = 300000000;
// 				break;
// 			case '4':
// 				speed = 200000000;
// 				break;
// 			default:
// 				return 1;
// 				break;
// 		}
// 		return 0;
// 	}
// 	else
// 	{
// 		return 1;
// 	}
// }

int main_snake(char** option)
{
	int result;
	// if (result = checkOption(option))
	// {
	// 	printf("Error option, please enter like snake -s 1.\n");
	// 	return result;
	// }
	initSnake();
	printScreen();
	startGame();
	return 0;
}

