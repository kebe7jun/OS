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
		int x = 123;
		scanf("%d", &x);
		printf("%d\n", x);
	}
	while(1);
    return 0;
}
