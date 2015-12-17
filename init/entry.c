#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "irq.h"
#include "apps/shell.h"

int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	idt_init();
	kb_init();

	// irq_install();
	timer_install();
	main_shell();
	while(1);
    return 0;
}
