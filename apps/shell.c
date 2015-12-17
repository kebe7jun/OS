/*************************************************************************
	> File Name: apps/shell.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月16日 星期三 08时27分38秒
 ************************************************************************/

#include "stdio.h"
#include "string.h"
#include "system.h"
#include "time.h"
#include "apps/shell.h"
#include "apps/showTime.h"
#include "apps/2048games.h"

#define SHELL_MAX_LENGTH 1024

void dealShell(char* shell)
{
	int result = 0;
	if (!strcmp(shell, "reboot"))
	{
		reboot();
	}
	else if (!strcmp(shell, "time"))
	{
		result = main_show_time();
	}
	else if (!strcmp(shell, "game"))
	{
		game_play();
	}
	else if (!strcmp(shell, "help"))
	{
		printf("Usage 'commands [option]...' to call commands.\n");
		printf("This shell support the follows commands:\n");
		printf("reboot    ------ Reboot you system.\n");
		printf("time      ------ Show now system time.\n");
		printf("game      ------ Play 2048 game.\n");
		printf("help      ------ Show the help documents.\n");
	}
	else if (!strcmp(shell, ""))
	{
		//Nothing to do.
	}
	else
	{
		printf("Sorry, the command you just inputed is not supported, if you have any question, run help\n");
	}

	if (result)
	{
		printf("Error, the %s return code(%d)!\n", shell, result);
	}
}

//Main function.
int main_shell()
{
	char sh[SHELL_MAX_LENGTH];
	while(1)
	{
		setTextColor(rc_light_red, rc_magenta);
		printf("Shell >");
		setTextColor(rc_black, rc_white);
		printf(" ");
		gets(sh);
		dealShell(sh);
	}
	return RUN_SUCCESS;
}
