#ifndef _SYSTEM_H
#define _SYSTEM_H 

extern void beep(unsigned short frequency, int time);
extern int is_386 ();
extern int is_486 ();
extern void newcpuid(unsigned long op, unsigned long v[4]);
extern int cpuinfo();
extern int has_cpuid ();
extern void getcpuid (char *);
extern int cpuid_init();
extern void print_cpuid(int i);
extern unsigned read_cmos(unsigned reg, char bcd);
extern int rand();
extern void srand(int new_seed);


extern void reboot();
#endif