#ifndef PAGING_H
#define PAGING_H

#include "kernel.h"

#define PAGE_S 4096

typedef struct page_t {
    byte p : 1;
    byte rw : 1;
    byte us : 1;
    byte pwt : 1;
    byte pcd : 1;
    byte a : 1;
    byte d : 1;
    byte ps : 1;
    byte g : 1;
    byte : 3;
    byte pat : 1;
    byte : 8;
    dword frame : 11;
    dword : 20;
    byte : 7;
    byte pk : 4;
    byte xd : 1;
} __attribute__((__packed__)) page_t;

typedef struct page_dir_t {
    page_t pages[512];
} __attribute__((__packed__)) page_dir_t;

typedef struct pdpte_t {
    byte p : 1;
    byte rw : 1;
    byte us : 1;
    byte pwt : 1;
    byte pcd : 1;
    byte a : 1;
    byte : 6;
    dword dir : 20;
    dword : 31;
    byte xd : 1;
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
void map_page(page_dir_t* dir, qword virt, qword phys, bool rw, bool us, bool exec);

/* Tries to allocate a 4 KByte aligned and 4 KByte large area */
void* alloc_page_struct();

/* Frees a pointer returned by alloc_page_struct */
void free_page_struct(void* ptr);

/* Flushes all pages by reloading cr3 */
static inline void flush_pages() { __asm("movq %cr3, %rax\nmovq %rax, %cr3"); }

#endif // #ifndef PAGING_H
