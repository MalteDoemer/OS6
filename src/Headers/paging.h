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
    byte pat : 1;
    byte g : 1;
    byte : 3;
    dword frame : 20;
    dword : 27;
    byte pk : 4;
    byte xd : 1;
} page_t;

typedef struct page_table_t {
    page_t pages[512];
} page_table_t;

typedef struct page_dir_entry_t {
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

typedef struct page_dir_t {
    page_dir_entry_t entries[512];
} page_dir_t;

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
} pdpte_t;

typedef struct pdpt_t {
    pdpte_t directories[512];
} pdpt_t;

void init_paging();

page_dir_t* mk_page_dir();
page_table_t* mk_page_table();

page_dir_entry_t get_entry(page_table_t* table);

void* alloc_page_struct();
void free_page_struct(void* ptr);

void switch_page_dir(page_dir_t* page_dir);
void flush_pages();

#endif // #ifndef PAGING_H
