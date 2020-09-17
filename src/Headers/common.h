#ifndef COMMON_H
#define COMMON_H

#include "kernel.h"

/* Write a byte to a port */
static inline void outb(word port, byte val) { __asm volatile("outb %0, %1" : : "a"(val), "Nd"(port)); }

/* Write a word to a port */
static inline void outw(word port, word val) { __asm volatile("outw %0, %1" : : "a"(val), "Nd"(port)); }

/* Read a byte from a port */
static inline byte inb(word port)
{
    byte ret;
    __asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Read a word from a port */
static inline word inw(word port)
{
    word ret;
    __asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Clears the interrupt flag */
static inline void cli() { __asm("cli"); }

/* Sets the interrupt flag */
static inline void sti() { __asm("sti"); }

/* Halts the cpu */
static inline void hlt() { __asm("hlt"); }

/* Sets all bytes in a buffer */
void* memsetb(void* s, byte val, size_t n);

/* Copy bytes to buffer */
void* memcpyb(void* dest, const void* src, size_t n);

/* Sets all words in a buffer */
void* memsetw(void* s, word val, size_t n);

/* Copy words to buffer */
void* memcpyw(void* dest, const void* src, size_t n);

/* Sets all dwords in a buffer */
void* memsetd(void* s, dword val, size_t n);

/* Copy dwords to buffer */
void* memcpyd(void* dest, const void* src, size_t n);

/* Sets all qwords in a buffer */
void* memsetq(void* s, qword val, size_t n);

/* Copy qwords to buffer */
void* memcpyq(void* dest, const void* src, size_t n);

/* Get the length of a null-terminated string */
size_t strlen(char* str);

/* Compare to strings for equality */
bool strcmp(char* str1, char* str2);

#endif // #ifndef COMMON_H
