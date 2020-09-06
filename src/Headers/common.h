#ifndef COMMON_H
#define COMMON_H

#include "kernel.h"

static inline void outb(word port, byte val)
{
    __asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline void outw(word port, word val)
{
    __asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline byte inb(word port)
{
    byte ret;
    __asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline word inw(word port)
{
    word ret;
    __asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void cli()
{
    __asm ("cli");
}

static inline void sti()
{
    __asm ("sti");
}

void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

size_t strlen(char* str);
bool strcmp(char* str1, char* str2);


#endif // #ifndef COMMON_H
