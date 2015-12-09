#include "console.h"

int kern_entry()
{
	// const char *str = "my first kernel with keyboard support";
	// clear_screen();
	// kprint(str);
	// kprint_newline();
	// kprint_newline();
	console_clear();
	idt_init();
	kb_init();

	while(1);
    return 0;
}
