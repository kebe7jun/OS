#ifndef _STDIO_H
#define _STDIO_H


#ifndef NULL
    #define NULL 0
#endif

#ifndef SCANF_MAX_BUFFER_LENGTH
#define SCANF_MAX_BUFFER_LENGTH 4096
#endif

#ifndef RUN_SUCCESS
#define RUN_SUCCESS 0
#endif

typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef          char  int8_t;
typedef unsigned long time_t;

//Color
typedef
enum real_color {
    rc_black = 0,
    rc_blue = 1,
    rc_green = 2,
    rc_cyan = 3,
    rc_red = 4,
    rc_magenta = 5,
    rc_brown = 6,
    rc_light_grey = 7,
    rc_dark_grey = 8,
    rc_light_blue = 9,
    rc_light_green = 10,
    rc_light_cyan = 11,
    rc_light_red = 12,
    rc_light_magenta = 13,
    rc_light_brown  = 14,   // yellow
    rc_white = 15
} real_color_t;

// 清屏操作
void console_clear();

// // 屏幕输出一个字符  带颜色
// void console_putc_color(char c, real_color_t back, real_color_t fore);

// // 屏幕打印一个以 \0 结尾的字符串  默认黑底白字
// void console_write(char *cstr);

// // 屏幕打印一个以 \0 结尾的字符串  带颜色
// void console_write_color(char *cstr, real_color_t back, real_color_t fore);

// // 屏幕输出一个十六进制的整型数
// void console_write_hex(uint32_t n, real_color_t back, real_color_t fore);

// // 屏幕输出一个十进制的整型数
// void console_write_dec(uint32_t n, real_color_t back, real_color_t fore);

/*

Now support %s %d %c %p %x format
*/

void putch_color_pos(char c, real_color_t back, real_color_t fore, int x, int y);
void printf(const char *format , ...);
/*
Now support %s %c %d
*/
int scanf(const char *format, ...);

void gets(char *chs);

// Press key.
void onKeyDown(char keycode);

//Key relese.
void onKeyUp(char keycode);

//Set the keypressed callable function
void registerListenKey(void (*function)(char keycode));

//Set the test color to show.
void setTextColor(real_color_t back, real_color_t front);

#endif
