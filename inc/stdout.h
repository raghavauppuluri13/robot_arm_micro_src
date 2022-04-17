#ifndef __STDOUT_H__
#define __STDOUT_H__
#include "stm32f0xx.h"
#include <stdio.h>
#include <stdarg.h>


void init_usart(void);
void smintf(const char *format, ...);
void print_integer(int n, int radix, char* prefix);

#endif
