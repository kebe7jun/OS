#include "stdio.h"
#include "keyboard_map.h"


// VGA 的显示缓冲的起点是 0xB8000
static uint16_t *video_memory = (uint16_t *)0xB8000;


// 屏幕"光标"的坐标
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static uint8_t is_shift_down = 0;
static uint8_t font_size = 80;
static real_color_t now_set_color_back = rc_black;
static real_color_t now_set_color_front = rc_white;

static void move_cursor()
{
    // 屏幕是 80 字节宽
    uint16_t cursorLocation = cursor_y * font_size + cursor_x;

    // 在这里用到的两个内部寄存器的编号为14与15，分别表示光标位置
    // 的高8位与低8位。

    outb(0x3D4, 14);                    // 告诉 VGA 我们要设置光标的高字节
    outb(0x3D5, cursorLocation >> 8);   // 发送高 8 位
    outb(0x3D4, 15);                    // 告诉 VGA 我们要设置光标的低字节
    outb(0x3D5, cursorLocation);        // 发送低 8 位
}

void console_clear()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);

    int i;
    for (i = 0; i < font_size * 25; i++)
    {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}


static void scroll()
{
    // attribute_byte 被构造出一个黑底白字的描述格式
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);  // space 是 0x20

    // cursor_y 到 25 的时候，就该换行了
    if (cursor_y >= 25)
    {
        // 将所有行的显示数据复制到上一行，第一行永远消失了...
        int i;

        for (i = 0 * font_size; i < 24 * font_size; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // 最后的一行数据现在填充空格，不显示任何字符
        for (i = 24 * font_size; i < 25 * font_size; i++)
        {
            video_memory[i] = blank;
        }

        // 向上移动了一行，所以 cursor_y 现在是 24
        cursor_y = 24;
    }
}


void putch_color(char c, real_color_t back, real_color_t fore)
{
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;

    // 0x08 是退格键的 ASCII 码
    // 0x09 是tab 键的 ASCII 码
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }
    else if (c == '\r')
    {
        cursor_x = 0;
    }
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ')
    {
        video_memory[cursor_y*80 + cursor_x] = c | attribute;
        cursor_x++;
    }

    // 每 80 个字符一行，满80就必须换行了
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    // 如果需要的话滚动屏幕显示
    scroll();

    // 移动硬件的输入光标
    move_cursor();
}

void putch_color_pos(char c, real_color_t back, real_color_t fore, int x, int y)
{
    cursor_x = x;
    cursor_y = y;
    putch_color(c, back, fore);
}

void console_write(char *cstr)
{
    while (*cstr)
    {
        putch(*cstr++);
    }
}

void putch(char c)
{
    putch_color(c, now_set_color_back, now_set_color_front);
    // if (ch == '\b')
    // {
    //     putch(' ');
    //     putch('\b');
    // }
}

void console_write_uint32_t(uint32_t t)
{

    uint32_t tmp = 1000000000;
    uint32_t tmp1;
    char isFind = 0;
    while(tmp)
    {
        tmp1 = t/tmp;
        t = t%tmp;
        if (tmp1)
        {
            putch('0'+tmp1);
            isFind = 1;
        }
        else
        {
            if (isFind)
            {
                putch('0');
            }
        }
        tmp = tmp/10;
    }

}

void console_write_uint8_t(uint8_t t)
{

    uint8_t tmp = 100;
    uint8_t tmp1;
    char isFind = 0;
    while(tmp)
    {
        tmp1 = t/tmp;
        t = t%tmp;
        if (tmp1)
        {
            putch('0'+tmp1);
            isFind = 1;
        }
        else
        {
            if (isFind)
            {
                putch('0');
            }
        }
        tmp = tmp/10;
    }

}

void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
    while (*cstr)
    {
        putch_color(*cstr++, back, fore);
    }
}


void itoa (char *buf, int base, int d)
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put `-' in the head. */
    if (base == 'd' && d < 0)
    {
        *p++ = '-';
        buf++;
        ud = -d;
    }
    else if (base == 'x')
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do
    {
        int remainder = ud % divisor;

        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    }
    while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2)
    {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void printf (const char *format, ...)
{
    char **arg = (char **) &format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0)
    {
        if (c != '%')
            putch(c);
        else
        {
            char *p;

            c = *format++;
            switch (c)
            {
            case 'd':
            case 'u':
            case 'x':
                itoa (buf, c, *((int *) arg++));
                p = buf;
                while (*p)
                    putch (*p++);
                break;

            case 's':
                p = *arg++;
                if (! p)
                    p = "(null)";

                while (*p)
                    putch (*p++);
                break;

            default:
                putch (*((int *) arg++));
                break;
            }
        }
    }
}

char getCharByKeyCode(char keycode)
{
    char ch;
    if (keycode == 42 || keycode == 54)
    {
        is_shift_down = 1;
    }
    ch = keyboard_map[keycode];
    if (is_shift_down)
    {
        if (ch>='a' && ch <= 'z')
        {
            ch += 'A' - 'a';
        }
        else if (ch>='A' && ch<='Z')
        {
            ch += 'a' - 'A';
        }
        else
        {
            ch = keyboard_map_1[keycode];
        }
    }
    return ch;
}


void gets(char *chs)
{
    char ch;
    int pos = 0;
    int keycode;
    do
    {
        keycode = getch();
        ch = getCharByKeyCode(keycode);
        keycode = -1;
        if (ch == '\b')
        {
            if (pos>0)
            {
                pos--;
                putch('\b');
                putch(' ');
                putch('\b');
            }
        }
        else
        {
            if (ch && ch != (char)27)
            {
               chs[pos++] = ch;
                putch(ch);
            }
        }

    }
    while(ch!='\n');
    chs[pos-1] = '\0';
}
int scanf(const char *format, ...)
{
    char ch;
    int pos = 0;
    int pos1 = 0;
    int keycode;
    char *p;
    char **arg = (char **) &format;
    char scanfStr[SCANF_MAX_BUFFER_LENGTH];
    arg++;
    gets(scanfStr);
    pos = 0;
    while(*format)
    {
        if (*format == '%')
        {

            char tmp[SCANF_MAX_BUFFER_LENGTH];
            ch = *++format;
            pos1 = 0;

            p = *arg++;
            while(scanfStr[pos] == ' ') pos++;  //Clear space
            switch(ch)
            {
            case 'd':
                while(scanfStr[pos] != ' ' && scanfStr[pos])
                {
                    tmp[pos1++] = scanfStr[pos++];
                }
                tmp[pos1++] = '\0';
                *(int*)p = convertStringToInt(tmp);
                break;
            case 'c':
                *p = scanfStr[pos++];
                break;
            case 's':
                while(scanfStr[pos] != ' ' && scanfStr[pos])
                {
                    tmp[pos1++] = scanfStr[pos++];
                }
                tmp[pos1++] = '\0';
                strcpy(p, tmp);
                break;
            }
        }
        format++;
    }
    return 0;
}

void setTextColor(real_color_t back, real_color_t front)
{
    now_set_color_back = back;
    now_set_color_front = front;
}

static void (*onGetKeyFunction)(char keycode);
static int isSendKeyCode = 0;
void registerListenKey(void (*function)(char keycode))
{
    onGetKeyFunction = function;
    isSendKeyCode = 0;
}

void onKeyDown(char keycode)
{
    // printf("%c", ch);
    if (onGetKeyFunction && !isSendKeyCode)
    {
        (*onGetKeyFunction)(keycode); //Call
        isSendKeyCode = 1;
    }
    // putch(ch);
}

void onKeyUp(char keycode)
{
    switch(keycode)
    {
        case 42:
        case 54:    //Shift up envent.
            is_shift_down = 0;
            break;
    }
}

