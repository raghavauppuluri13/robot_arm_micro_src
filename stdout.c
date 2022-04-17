/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#include "inc/stdout.h"

void init_usart() {
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART5EN;

    GPIOC->MODER &= (3 << 2 * 12);
    GPIOC->MODER |= (2 << 2 * 12);
    GPIOC->AFR[1] &= 0xf << (4 * 4);
    GPIOC->AFR[1] |= 2 << (4 * 4);

    GPIOD->MODER &= (3 << 2 * 2);
    GPIOD->MODER |= (2 << 2 * 2);
    GPIOD->AFR[0] &= 0xf << (4 * 2);
    GPIOD->AFR[0] |= 2 << (4 * 2);

    USART5->CR1 &= ~USART_CR1_UE;
    USART5->BRR = 48000000 / 115200;
    USART5->CR1 &= ~USART_CR1_M;
    USART5->CR2 &= ~USART_CR2_STOP;
    USART5->CR1 &= ~USART_CR1_OVER8;

    USART5->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    while (!(USART5->ISR & USART_ISR_TEACK)) { }
    while (!(USART5->ISR & USART_ISR_REACK)) { }
}

void smintf(const char *format, ...) {
    va_list more_args;
    va_start(more_args, format);

    for(int i = 0; format[i] != '\0'; i++) {
        if(format[i] == '%') {
            char* str;

            switch(format[i+1]) {
                case 'd':
                    print_integer(va_arg(more_args, int), 10, "");
                    i++;
                    break;

                case 'x':
                    print_integer(va_arg(more_args, int), 16, "0x");
                    i++;
                    break;

                case 'b':
                    print_integer(va_arg(more_args, int), 2, "0b");
                    i++;
                    break;

                case 's':
                    str = va_arg(more_args,char*);
                    for(int j = 0; str[j] != '\0'; j++) {
                        fputc(str[j],stdout);
                    }
                    i++;
                    break;

                case 'c':
                    fputc(va_arg(more_args,int),stdout);
                    i++;
                    break;

                case '%':
                    fputc('%',stdout);
                    i++;
                    break;
                default:
                    fputc('%',stdout);
            }
        }
        else {
            fputc(format[i],stdout);
        }
    }

    va_end(more_args);
}


int __io_putchar(int c) {
    if(c == '\n') {
        while(!(USART5->ISR & USART_ISR_TXE)) { }
        USART5->TDR = '\r';
    }
    while(!(USART5->ISR & USART_ISR_TXE)) { }
    USART5->TDR = c;
    return c;
}


// Recursively prints the remainder digits of a radix to reprsent a given
// number in the base specified by the radix
static void _print_integer_recur(unsigned int n, int radix) {
    int digit;
    if(n != 0) {
        _print_integer_recur(n / radix, radix);
        digit = n % radix;

        if(digit < 10) {
            fputc('0' + digit, stdout);
        }
        else {
            fputc('a' + (digit - 10), stdout);
        }
    }
}


// Prints a given integer value in a representation based on radix
// and adds a prefix directly to the left of the first digit
void print_integer(int n, int radix, char* prefix) {
    unsigned int abs_n = n > 0 ? n : -n;
    if(n < 0) {
        putchar('-');
    }

    // Print prefix
    for(int i = 0; prefix[i] != '\0'; i++) {
        putchar(prefix[i]);
    }

    if(n == 0) {
        putchar('0');
    }
    else {
        _print_integer_recur(abs_n,radix);
    }
}
