#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "irq.h"

int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	printf("%s\n", "Welcome to use 7JunOS!");
	idt_init();
	kb_init();

	// irq_install();
	timer_install();

	srand(time());
	while(1){
		x = getch();
		printf("%d\n", x);
		printf("%d\n", time());
		printf("%d\n", rand());
	}
	while(1);
    return 0;
}
