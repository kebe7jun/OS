#include "stdio.h"
#include "conio.h"

int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	printf("%s\n", "Welcome to use 7JunOS!");
	idt_init();
	kb_init();
	while(1){
		x = getch();
		printf("%d\n", x);
	}
	while(1);
    return 0;
}
