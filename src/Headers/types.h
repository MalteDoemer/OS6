#ifndef TYPES_H
#define TYPES_H

#define NULL 0

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;
typedef unsigned long long size_t;

enum bool { false = 0, true = 1 } __attribute__((__packed__));

typedef enum bool bool;

#endif // #ifndef TYPES_H
