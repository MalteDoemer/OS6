#include "kernel.h"

heap_t kheap;

heap_t make_heap(void* start, size_t size)
{
    heap_t res;
    res.size = size;
    res.start = (chunk_t*)start;
    res.start->size = size - sizeof(chunk_t);
    res.start->allocated = false;
    res.start->next = NULL;
    res.start->prev = NULL;
    res.start->magic = HEAP_MAGIC;
    return res;
}

void* heap_alloc(heap_t heap, size_t size)
{
    chunk_t* chunk = heap.start;

    while (chunk && chunk->allocated)
        chunk = chunk->next;

    if (!chunk)
        return NULL;

    if (chunk->size >= size + sizeof(chunk_t) + 1) {
        chunk_t* temp = (chunk_t*)((qword)chunk + sizeof(chunk_t) + size);

        temp->allocated = false;
        temp->size = chunk->size - size - sizeof(chunk_t);
        temp->magic = HEAP_MAGIC;

        chunk_t* next = chunk->next;

        temp->next = next;

        if (next)
            next->prev = temp;

        chunk->next = temp;
        temp->prev = chunk;
    }

    chunk->allocated = true;

    return (void*)((qword)chunk + sizeof(chunk_t));
}

void heap_free(heap_t heap, void* ptr)
{
    chunk_t* chunk = (chunk_t*)((qword)ptr - sizeof(chunk_t));
    if (chunk->magic != HEAP_MAGIC)
        return;

    chunk->allocated = false;

    if (chunk->prev != NULL && !chunk->prev->allocated) {
        chunk->prev->next = chunk->next;
        chunk->prev->size += chunk->size + sizeof(chunk_t);
        if (chunk->next != NULL)
            chunk->next->prev = chunk->prev;

        chunk = chunk->prev;
    }

    if (chunk->next != NULL && !chunk->next->allocated) {
        chunk->size += chunk->next->size + sizeof(chunk_t);
        chunk->next = chunk->next->next;
        if (chunk->next != NULL)
            chunk->next->prev = chunk->prev;

        chunk = chunk->prev;
    }
}

void* kmalloc(size_t size) { return heap_alloc(kheap, size); }

void kfree(void* ptr) { heap_free(kheap, ptr); }

void init_kheap() { kheap = make_heap((void*)0x200000, 0x100000); }