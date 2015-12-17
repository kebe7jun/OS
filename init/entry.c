#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "irq.h"
#include "games.h"
int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	printf("%s\n", "Welcome to use 7JunOS!");
	idt_init();
	kb_init();

	// irq_install();
	timer_install();
	printf("start games ~~~\n" );
	game_play();
	while(1);
    return 0;
}
