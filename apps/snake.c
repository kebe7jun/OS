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

	
	
static Snake snake;	//Store the snake like list info.
static Snake *head;	//The snake head.

static uint32_t bodySize = 0;		//The snake init size is zero.
static uint32_t startMem = 0xf00000;		//The start pos to store snake info in memory.

static char nowX = 0;	//The current snake head X pos.
static char nowY = 0;	//The current snake head Y pos.
static char foodX = 0;		//The current food X pos.
static char foodY = 0;	//The current food Y pos.

static int speed = 300000000;	//The default speed.
static uint32_t score = 0;		//The default score gotten is zero.

//Nww a snake node from memory.
Snake *newSnake()
{
	Snake *s;
	int p = startMem + bodySize*sizeof(Snake);
	if (p>=0xffffff)	//If out of the memoey, set p to init pos.
	{
		p = startMem;
	}
	s = (Snake*)p;
	bodySize++;		//Let snake body size incerese.
	s->next = NULL;
	return s;
}

//Now a food.
void newFood()
{
	int fx, fy;
	int valid = 1;
	Snake *s = snake.next;
	srand(time(NULL));		//Set the timer seek.
	while(1)
	{
		fx = abs(rand())%70;		//Get the pos of new food.
		fy = abs(rand())%20;
		while(s)
		{
			if (fx == s->x && fy == s->y)
			{
				valid = 0;
			}
			s = s->next;
		}
		if (valid)		//If the new pos is valid, good.
		{
			break;
		}
	}
	foodX = fx;
	foodY = fy;
	score += speed/100000000;	//Set the score.
}

//Init the snake.
void initSnake()
{
	Snake *s, *s1;
	s = newSnake();		//New 3 nodes.
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
	newFood();		//New food.
}

//Print the snake body and others info.
void printScreen()
{
	Snake *s = snake.next;
	int i;
	console_clear();
	while(s->next)
	{
		putch_color_pos('*', rc_black, rc_white, s->x, s->y);		//Print snake body.
		s = s->next;
	}
	putch_color_pos('@', rc_black, rc_white, s->x, s->y);		//Snake head.
	putch_color_pos('#', rc_black, rc_green, foodX, foodY);	//Food.

	for (i = 0; i < 20; ++i)		//The boder.
	{
		putch_color_pos('|', rc_black, rc_white, 70, i);	
	}

	for (i = 0; i < 70; ++i)
	{
		putch_color_pos('-', rc_black, rc_white, i, 20);	
	}

	putch_color_pos('\0', rc_black, rc_white, 70, 5);
	printf("Score: %d\n", score);		//Print score.
	putch_color_pos(' ', rc_black, rc_white, 79, 24);
}

//Move the snake to a new pos.
int moveSnake(char toX, char toY)
{
	int newX, newY;
	Snake *s;
	newX = head->x+toX;
	newY = head->y+toY;
	nowX = toX;
	nowY = toY;
	if (newX<0 || newY <0 || newX >=70 || newY >=20)		//Check border.
	{
		printf("End!\n");
		return 1;
	}
	s = snake.next;
	while(s)		//Check the snake eat self?
	{
		if (newX == s->x && newY == s->y)
		{
			printf("End!\n");
			return 1;
		}
		s = s->next;
	}
	s = newSnake();		//New a body.
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
	printScreen();//Print new snake ifno.
	return 0;
}


void startGame()	//Start Game.
{
	int key;
	int result;
	printScreen();
	while(1)
	{
		key = getchInStep(speed);	//Get user input.
		if (key == ESC_KEY)		//If user press ESC, exit Game.
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

int checkOption(char** option)
{
	char s;
	if (strcmp(option[1], "-s"))
	{
		s = option[2][0];
		switch(s)
		{
			case '1':
				speed = 700000000;
				break;
			case '2':
				speed = 500000000;
				break;
			case '3':
				speed = 300000000;
				break;
			case '4':
				speed = 200000000;
				break;
			default:
				return 1;
				break;
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

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

