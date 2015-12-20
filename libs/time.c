/*************************************************************************
	> File Name: time.c
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月15日 星期二 15时54分43秒
 ************************************************************************/

#include "time.h"
#include "stdio.h"
#include "system.h"
static unsigned long int next = 1;

/* System runtime */
int timer_ticks = 0;
volatile unsigned long int _thours = 00;
volatile unsigned long int _tminutes = 00;
volatile unsigned long int _tseconds = 00;

/* 18.222Hz  =  ~18 ticks / second 
   reset to 100Hz = 100 ticks /second */
void timer_handler(struct regs *r)
{
    /* update timer */
    timer_ticks++;

    /* Display x every second */
    if (timer_ticks % 100 == 0)
    {
        _tseconds++;
         
        if( _tseconds == 60 )
        {
            _tminutes++;
            _tseconds = 00;
            
            if(_thours == 60)
            {
               _thours++;
               _tminutes = 00;
            }
        }
    }
}

void timer_change_freq (int hz)
{
  int divisor = 1193180 / hz;
  outb (0x43, 0x36);
  outb (0x40, divisor & 0xFF);
  outb (0x40, divisor >> 8);
}

void print_time()
{
     printf("%d:%d:%d\n", _thours, _tminutes, _tseconds);
}

/* Waits for the given time */
void sleep(int ticks)
{
    unsigned long eticks;
    time_t t1 = time(NULL);
    eticks = t1 + ticks;
    while(t1 < eticks)
      t1 = time(NULL);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    timer_change_freq(100);
    irq_install_handler(0, timer_handler);
}

static long days_between_dates(unsigned start_year, unsigned start_day,
    int end_year, unsigned end_day)
{
  int fourcents, centuries, fouryears, years;
  long days;

  fourcents = end_year / 400 - start_year / 400;
  centuries = end_year / 100 - start_year / 100 -
/* subtract from 'centuries' the centuries already accounted for by
'fourcents' */
    fourcents * 4;
  fouryears = end_year / 4 - start_year / 4 -
/* subtract from 'fouryears' the fouryears already accounted for by
'fourcents' and 'centuries' */
    fourcents * 100 - centuries * 25;
  years = end_year - start_year -
/* subtract from 'years' the years already accounted for by
'fourcents', 'centuries', and 'fouryears' */
    400 * fourcents - 100 * centuries - 4 * fouryears;
/* add it up: 97 leap days every fourcent */
  days = (365L * 400 + 97) * fourcents;
/* 24 leap days every residual century */
  days += (365L * 100 + 24) * centuries;
/* 1 leap day every residual fouryear */
  days += (365L * 4 + 1) * fouryears;
/* 0 leap days for residual years */
  days += (365L * 1) * years;
/* residual days (need the cast!) */
  days += ((long)end_day - start_day);
/* account for terminal leap year */
  if(end_year % 4 == 0 && end_day >= 60)
  {
    days++;
    if(end_year % 100 == 0)
      days--;
    if(end_year % 400 == 0)
      days++;
  }
  if(end_year >= 0)
  {
    days++;
    if(end_year % 4 == 0)
      days--;
    if(end_year % 100 == 0)
      days++;
    if(end_year % 400 == 0)
      days--;
  }
  if(start_year > 0)
    days--;
  return days;
}

#define EPOCH_YEAR  1970
#define EPOCH_DAY 0 /* Jan 1 */

static unsigned long date_time_to_time_t(unsigned year, unsigned month,
    unsigned date, unsigned hour, unsigned min, unsigned sec)
{
  static const unsigned days_to_date[12] =
  {
/*              jan  feb  mar  apr  may  jun  jul  aug  sep  oct  nov  dec */
    0,
    31,
    31 + 28,
    31 + 28 + 31,
    31 + 28 + 31 + 30,
    31 + 28 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31,
    31 + 28 + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30
  };
/**/
  unsigned long rv;
  unsigned day;

/* convert month and year to day-in-year */
  if(month < 1 || month > 12 || date < 1 || date > 31)
    return 0;
  month--;
  date--;
  day = date + days_to_date[month];
/* convert to Unix JDN (UJDN) */
  rv = days_between_dates(EPOCH_YEAR, EPOCH_DAY, year, day);
/* convert from days to seconds, adding time as you go */
  rv *= 24;
  rv += hour;
  rv *= 60;
  rv += min;
  rv *= 60;
  rv += sec;
  return rv;
}

//Get the time now, return seconds from 1970.1.1 to now.
time_t time(time_t *timer)
{
  static signed char bcd = -1;
/**/
  unsigned portval, timeout, month, date, hour, minute, second;
  time_t rv;
  int year;

/* read register B to check for BCD or binary mode */
  if(bcd == -1)
  {
    outb(0x70, 0x0B);
    if(inb(0x71) & 0x04)
      bcd = 0;
    else
      bcd = 1;
  }
  while(1)
  {
/* is there an update cycle in progress? */
    outb(0x70, 0x0A);
    if((inb(0x71) & 0x80) == 0)
      break;
/* yes, enable end-of-update interrupt */
    outb(0x70, 0x0B);
    portval = inb(0x71);
    outb(0x71, portval | 0x10);
/* sleep until end-of-update interrupt, or for 5 ms
If RTC chip has 32.768 KHz crystal, update should take about 2 ms */
    timeout = 5;
    sleep(timeout);
/* disable end-of-update interrupt
    outb(0x70, 0x0B); */
    outb(0x71, portval & ~0x10);
  }
/* get year/month/date
  year = read_cmos(9, bcd) + 1900;  OH NO, Y2K!
  year = read_cmos(9, bcd) + 2000;
use the Microsoft method -- this should be good from 1970-2069
signed 32-bit time_t will overflow before then, in 2038 */
  year = read_cmos(9, bcd); /* 0-99 */
  if(year < 70)
    year += 2000;
  else
    year += 1900;
  month = read_cmos(8, bcd);  /* 1-12 */
  date = read_cmos(7, bcd); /* 1-31 */
/* get time */
  hour = read_cmos(4, bcd); /* 0-23 */
  minute = read_cmos(2, bcd); /* 0-59 */
  second = read_cmos(0, bcd); /* 0-59 */

  rv = date_time_to_time_t(year, month, date, hour, minute, second);
  if(timer != NULL)
    (*timer) = rv;
  return rv;
}


static int g_seed;

//Set the rand seek.
void srand(int new_seed)
{
  g_seed = new_seed;
}

//Get a randon number.
int rand()
{
  if(g_seed == 0)
    g_seed = 1;
  if((((g_seed << 3) ^ g_seed) & 0x80000000uL) != 0)
    g_seed = (g_seed << 1) | 1;
  else
    g_seed <<= 1;
  return g_seed - 1;
}
