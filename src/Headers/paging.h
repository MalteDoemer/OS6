#ifndef PAGING_H
#define PAGING_H

#include "kernel.h"

#define PAGE_SIZE 0x100000

typedef struct page_t {
    uint8_t p : 1;
    uint8_t rw : 1;
    uint8_t us : 1;
    uint8_t pwt : 1;
    uint8_t pcd : 1;
    uint8_t a : 1;
    uint8_t d : 1;
    uint8_t ps : 1;
    uint8_t g : 1;
    uint8_t : 3;
    uint8_t pat : 1;
    uint8_t : 8;
    uint32_t frame : 11;
    uint32_t : 20;
    uint8_t : 7;
    uint8_t pk : 4;
    uint8_t xd : 1;
} __attribute__((__packed__)) page_t;

typedef struct page_dir_t {
    page_t pages[512];
} __attribute__((__packed__)) page_dir_t;

typedef struct pdpte_t {
    uint8_t p : 1;
    uint8_t rw : 1;
    uint8_t us : 1;
    uint8_t pwt : 1;
    uint8_t pcd : 1;
    uint8_t a : 1;
    uint8_t : 6;
    uint32_t dir : 20;
    uint32_t : 31;
    uint8_t xd : 1;
} __attribute__((__packed__)) pdpte_t;

typedef struct pdpt_t {
    pdpte_t directories[512];
} __attribute__((__packed__)) pdpt_t;

/* Initialize paging */
void init_paging();

/* Make a new page directory with the kernel already mapped */
page_dir_t* make_page_dir();

/* Sets the first entry of the page directory pointer table and flushes all pages */
void set_activ_dir(page_dir_t* dir);

/* maps a 2 MBytes page with the specified flags */
void map_page(page_dir_t* dir, uint64_t virt, uint64_t phys, bool rw, bool us, bool exec);

uint64_t allocate_page_frame();

void free_page_frame(uint64_t addr);

/* Tries to allocate a 4 KByte aligned and 4 KByte large area */
void* alloc_page_struct();

/* Frees a pointer returned by alloc_page_struct */
void free_page_struct(void* ptr);

/* Flushes all pages by reloading cr3 */
static inline void flush_pages()
{
    __asm("movq %cr3, %rax\nmovq %rax, %cr3");
}

#endif // #ifndef PAGING_H
