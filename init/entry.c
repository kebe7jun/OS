#include "stdio.h"
#include "conio.h"
#include "time.h"
#include "irq.h"
<<<<<<< HEAD
#include "games.h"
=======
#include "apps/shell.h"

>>>>>>> 006d92c6caed50dd1f960e33b9f75dfe968a1f7e
int os_entry()
{
	int x;
	console_clear();	//Clear the screen.	
	idt_init();
	kb_init();

	// irq_install();
	timer_install();
<<<<<<< HEAD
	printf("start games ~~~\n" );
	game_play();
=======
	main_shell();
>>>>>>> 006d92c6caed50dd1f960e33b9f75dfe968a1f7e
	while(1);
    return 0;
}
