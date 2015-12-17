#include "stdio.h"
#include "time.h"
#include "conio.h"
#define  LEN 4
#define SPACE 32
#define A 97
#define W 119
#define D 100
#define S 115
#define EXIT 1
#define LEFT 75
#define UP 72
#define RIGHT 77
#define DOWN 80
/*
a  left 97
w top 119
d right 100
s  down 115
    space 32 
     ESC 27
*/
  //create boxes

void initBoxes(int digit[][LEN]);
int getSpace(int n);
void moveLeft(int digit[][LEN]);
void moveUp(int digit[][LEN]);
void moveRight(int digit[][LEN]);
void moveDown(int digit[][LEN]);
// void addLeft(int digit[][LEN]);
void show(int digit[][LEN]);
void keyDown(int digit[][LEN]);

int abs(int value)
{
	return value<0?-value:value;
}
int selectDigit()
{
	int d;
	d = abs(rand()%(LEN));
	return d%2 == 0? 2:4;
}
void initBoxes(int digit[][LEN])
{
	int temp;
	int posX,  posY;// the rand position
	srand((unsigned)time(NULL));
	posX = abs(rand()%(LEN));
	posY = abs(rand()%(LEN));
	// printf("%d, %d ",posX, posY);
	digit[posX][posY] = selectDigit();	
	while(1)
	{
		if(temp = abs(rand()%(LEN)) != posX)
		{
			posX = temp;
			break;
		}
	}
	while(1)
	{
		if(temp = abs(rand()%(LEN))  != posY)
		{
			posY = temp;
			break;
		}
	}
	// printf("%d, %d ",posX, posY);
	digit[posX][posY] = selectDigit();	
	// printf("%d\n", digit[posX][posY]);
	show(digit);
}
void createDigit(int digit[][LEN])
{
	int i, j, whichP;
	int posX,  posY;// the rand position
	int flag ;
	srand((unsigned)time(NULL));
	while(1)
	{
		flag = 1;
		posX = abs(rand()%(LEN));
		posY = abs(rand()%(LEN));
		for(i=0; i<LEN; i++)
		{
			for(j=0; j<LEN; j++)
			{
				if(digit[i][j] != 0 && posX == i && posY == j)// have the same
				{
					flag = 0;
					break;
				}
			}
			if(!flag)
			{
				break;
			}
		}
		if(flag)
		{
			digit[posX][posY] = selectDigit();	
			break;
		}
	}
}
int getSpace(int n)
{	
	if(n/10 == 0)//1
	{
		return LEN-1;
	}
	else if(n/100 == 0)//2
	{
		return LEN-2;
	}
	else if(n/1000 == 0)//3
	{
		return LEN-3;
	}
	else		//4
	{
		return LEN-4;
	}
}

void moveLeft(int digit[][LEN])
{
	int i, j;
	int pos, flag;
	for(i=0; i<LEN; i++)
	{
		pos = -1;
		flag = 0;
		for(j=0; j<LEN; j++)
		{
			if(digit[i][j] == 0 && !flag)//The first barrier positon
			{
				pos = j;
				flag = 1;
				// digit[i][j-1] = digit[i][j];
				// j--;
			}
			if(digit[i][j] != 0 && pos >= 0)
			{
				digit[i][pos] = digit[i][j];
				digit[i][j] = 0;

				pos = -1;
				flag = 0;
				j = 0;
			}
		}
	}
}
void moveUp(int digit[][LEN])
{
	int i, j;
	int pos, flag;
	for(i=0; i<LEN; i++)
	{
		pos = -1;
		flag = 0;
		for(j=0; j<LEN; j++)
		{
			if(digit[j][i] == 0 && !flag)//The first barrier positon
			{
				pos = j;
				flag = 1;
				// digit[i][j-1] = digit[i][j];
				// j--;
			}
			if(digit[j][i] != 0 && pos>=0)
			{
				digit[pos][i] = digit[j][i];
				digit[j][i] = 0;
				
				pos = -1;
				flag = 0;
				j = 0;
			}
		}
	}
}
void moveRight(int digit[][LEN])
{
	int i, j;
	int pos, flag;
	for(i=0; i<LEN; i++)
	{
		pos = LEN;
		flag = 0;
		for(j=LEN-1; j>=0; j--)
		{
			if(digit[i][j] == 0 && !flag)//The first barrier positon
			{
				pos = j;
				flag = 1;
				// digit[i][j-1] = digit[i][j];
				// j--;
			}
			if(digit[i][j] != 0 && pos<LEN)
			{
				digit[i][pos] = digit[i][j];
				digit[i][j] = 0;

				flag = 0;
				pos = LEN;
				j = LEN - 1;
			}
		}
	}
}
void moveDown(int digit[][LEN])
{
	int i, j;
	int pos, flag;
	int isFree = 1;
	for(i=0; i<LEN; i++)
	{
		pos = LEN;
		flag = 0;
		for(j=LEN-1; j>=0; j--)
		{
			// if(digit[i][j] == 0)
			// {
			// 	isFree = 0;
			// 	return;
			// }
			if(digit[j][i] == 0 && !flag)//The first barrier positon
			{
				pos = j;
				flag = 1;
				// digit[i][j-1] = digit[i][j];
				// j--;
			}
			if(digit[j][i] != 0 && pos<LEN)
			{
				digit[pos][i] = digit[j][i];
				digit[j][i] = 0;
				
				pos = LEN;
				 flag = 0;
				 j = LEN - 1;
			}
		}
	}
}
void addLeft(int digit[][LEN])
{
	int i, j;
	int temp;
	for(i=0; i<LEN; i++)
	{
		for(j=0; j<LEN; j++)
		{
			if(j+1<LEN && (temp = digit[i][j] )!= 0 && digit[i][j+1] != 0)
			{
				if(temp == digit[i][j+1])
				{
					digit[i][j] = temp + digit[i][j+1];
					digit[i][j+1] = 0;
				}
			}
		}
	}
}
void addRight(int digit[][LEN])
{
	int i, j;
	int temp;
	for(i=0; i<LEN; i++)
	{
		for(j=LEN; j>=0; j--)
		{
			if(j-1>=0 && (temp = digit[i][j] ) != 0 && digit[i][j-1] != 0)
			{
				if(temp == digit[i][j-1])
				{
					digit[i][j] = temp + digit[i][j-1];
					digit[i][j-1] = 0;
				}
			}
		}
	}
}
void addUp(int digit[][LEN])
{
	int i, j;
	int temp;
	for(i=0; i<LEN; i++)
	{
		for(j=0; j<LEN; j++)
		{
			if(j+1<LEN && (temp = digit[j][i] ) != 0 && digit[j+1][i] != 0)
			{
				if(temp == digit[j+1][i])
				{
					digit[j][i] = temp + digit[j+1][i];
					digit[j+1][i] = 0;
				}
			}
		}
	}
}
void addDown(int digit[][LEN])
{
	int i, j;
	int temp;
	for(j=LEN; j>=0; j--)
	{
		for(j=0; j<LEN; j++)
		{
			if(j-1>=0 && (temp = digit[j][i] ) != 0 && digit[j-1][i] != 0)
			{
				if(temp == digit[j+1][i])
				{
					digit[j][i] = temp + digit[j-1][i];
					digit[j-1][i] = 0;
				}
			}
		}
	}
}
void show(int digit[][LEN])
{
	int i, j, m, n;
	console_clear();	// Clear the screen
	for(i=0; i<LEN; i++)
	{
		for(j=0; j<LEN; j++)
		{
			if(digit[i][j] ==  0)
			{
				for(n=0; n<LEN; n++)
				{
					printf(" ");
				}			
			}
			else
			{
				printf("%d", digit[i][j]);
				for(m=0; m<getSpace(digit[i][j]); m++)
				{
					printf(" ");
				}
			}
			printf(" ");
		}
		printf("\n");
	}
}
void keyDown(int digit[][LEN])
{	int ch;
	while(1)
	{
		ch = getch();
	// printf("%d ", ch);
		switch (ch)
		{
			case LEFT :
				// printf("left\n");
				moveLeft(digit);
				addLeft(digit);
				moveLeft(digit);
				createDigit(digit);
				show(digit);
				break;
			case RIGHT :
				// printf("right\n");
				moveRight(digit);
				addRight(digit);
				moveRight(digit);
				createDigit(digit);
				show(digit);
				break;
			case UP:
				// printf("top\n");
				moveUp(digit);
				addUp(digit);
				moveUp(digit);
				createDigit(digit);
				show(digit);
				break;
			case DOWN:
				printf("down\n");
				moveDown(digit);
				// addDown(digit);
				// moveDown(digit);
				// createDigit(digit);
				show(digit);
				break;
			case EXIT:
				printf("exit\n");
				return ;
		}
	}
}
int game_play()
{
	int digit[LEN][LEN] = {0};
	initBoxes(digit);
	keyDown(digit);
	return 0;
}