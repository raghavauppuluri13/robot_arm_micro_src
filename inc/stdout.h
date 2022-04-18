#ifndef __STDOUT_H__
#define __STDOUT_H__
#include "stm32f0xx.h"
#include <stdio.h>
#include <stdarg.h>

#define BAUD_RATE 115200

void init_usart(void);
void smintf(const char *format, ...);
void print_integer(int n, int radix, char* prefix);
void printchar(uint8_t c);

#endif
