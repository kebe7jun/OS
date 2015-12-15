#include "system.h"


void newcpuid(unsigned long op, unsigned long v[4])
{
__asm__ ("cpuid": "=a" (v[0]), "=b" (v[1]), "=c" (v[2]), "=d" (v[3]):"a" (op));
}

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
