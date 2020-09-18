#ifndef TYPES_H
#define TYPES_H

#define NULL 0

typedef char int8_t;
typedef short int16_t;
typedef int int32_t;
typedef long long int64_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned long long size_t;

enum bool {
    false = 0,
    true = 1
} __attribute__((__packed__));

typedef enum bool bool;

#endif // #ifndef TYPES_H
