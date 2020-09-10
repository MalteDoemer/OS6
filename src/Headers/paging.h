#ifndef PAGING_H
#define PAGING_H

#include "kernel.h"

#define PAGE_S 4096

typedef struct page_t
{
    byte p : 1;
    byte rw : 1;
    byte us : 1;
    byte pwt : 1;
    byte pcd : 1;
    byte a : 1;
    byte d : 1;
    byte pat : 1;
    byte g : 1;
    byte : 3;
    dword frame : 20;
    dword : 27;
    byte pk : 4;
    byte xd : 1;
} page_t;

typedef struct page_table_t
{
    page_t pages[512];
} page_table_t;

typedef struct page_dir_entry_t
{
    byte p : 1;
    byte rw : 1;
    byte us : 1;
    byte pwt : 1;
    byte pcd : 1;
    byte a : 1;
    byte : 6;
    dword table : 20;
    dword : 31;
    byte xd : 1;
} page_dir_entry_t;

typedef struct page_dir_t
{
    page_dir_entry_t entries[512];
} page_dir_t;

extern page_table_t kernelpt1;
extern page_table_t kernelpt2;

void *get_page_addr(qword entry);
void add_page_dir(page_dir_t *page_dir);

#endif // #ifndef PAGING_H
