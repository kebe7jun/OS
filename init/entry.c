#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "irq.h"
#include "apps/shell.h"

/*
This is the entry of this OS.
*/
int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	idt_init();	// idt init
	kb_init();	//init Keyboard.

	// irq_install();
	timer_install();	//Timer install.
	main_shell();	//Run the shell.
	while(1);
    return 0;
}
