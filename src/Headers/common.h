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

static inline void hlt()
{
    __asm ("hlt");
}

byte* memsetb(byte* s, byte val, size_t n);
byte* memcpyb(byte* dest, const byte* src, size_t n);

word* memsetw(word* s, word val, size_t n);
word* memcpyw(word* dest, const word* src, size_t n);

dword* memsetd(dword* s, dword val, size_t n);
dword* memcpyd(dword* dest, const dword* src, size_t n);

qword* memsetq(qword* s, qword val, size_t n);
qword* memcpyq(qword* dest, const qword* src, size_t n);


size_t strlen(char* str);
bool strcmp(char* str1, char* str2);


#endif // #ifndef COMMON_H
