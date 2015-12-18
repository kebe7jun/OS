#include "system.h"
#include "common.h"
#include "time.h"



/* Needed for getting values from CMOS such as clock time etc */
unsigned read_cmos(unsigned reg, char bcd)
{
	unsigned high_digit, low_digit;

	outb(0x70, reg);
	high_digit = low_digit = inb(0x71);
	if(!bcd)
		return low_digit;
    /* convert from BCD to binary */
	high_digit >>= 4;
	high_digit &= 0x0F;
	low_digit &= 0x0F;
	return 10 * high_digit + low_digit;
}

/**
Reboot
*/
void reboot()
{
	printf("System rebooting...\n");
	// sleep(1);
	outb(0x64, 0xFE);
	printf("Sorry, reboot faild, please press the reset button.\n");
}