/*************************************************************************
	> File Name: common.h
	> Author: KEBE
	> Mail: mail@kebe7jun.com
	> Created Time: 2015年12月09日 星期三 13时15分03秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
#include "stdio.h"

// 端口写一个字节
void outb(uint16_t port, uint8_t value);

// // 端口读一个字节
uint8_t inb(uint16_t port);

// // 端口读一个字
uint16_t inw(uint16_t port);

#endif
