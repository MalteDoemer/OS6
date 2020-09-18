#ifndef KHEAP_H
#define KHEAP_H

#include "kernel.h"

#define HEAP_MAGIC 0x69367420

typedef struct chunk_t chunk_t;
typedef struct chunk_t {
    duint16_t magic;
    chunk_t* prev;
    chunk_t* next;
    size_t size : 63;
    bool allocated : 1;
} chunk_t;

typedef struct heap_t {
    chunk_t* start;
    size_t size;
} heap_t;

/* Create a new heap */
heap_t make_heap(void* start, size_t size);

/* Allocate on a heap */
void* heap_alloc(heap_t heap, size_t size);

/* Free memory of a heap */
void heap_free(heap_t heap, void* ptr);

/* Initialize the kernel heap */
void init_kheap();

/* Allocate on the kernel heap */
void* kmalloc(size_t size);

/* Free memory from the kernel heap */
void kfree(void* ptr);

#endif // #ifndef KHEAP_H
