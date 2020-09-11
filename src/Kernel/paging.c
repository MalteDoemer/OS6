#include "kernel.h"

bool page_struct_table[158];

page_table_t* kernel_page_table1;
page_table_t* kernel_page_table2;

page_dir_t* kernel_page_dir;

pdpt_t* root_pdpt;

void init_paging()
{
    page_struct_table[0] = true;
    page_struct_table[1] = true;
    page_struct_table[2] = true;
    page_struct_table[3] = true;
    page_struct_table[4] = true;

    root_pdpt = (pdpt_t*)0x2000;
    kernel_page_dir = (page_dir_t*)0x3000;
    kernel_page_table1 = (page_table_t*)0x4000;
    kernel_page_table2 = (page_table_t*)0x5000;
}

page_dir_t* mk_page_dir()
{
    page_dir_t* dir = alloc_page_struct();
    memsetb((byte*)dir, 0, sizeof(page_dir_t));

    return dir;
}

page_table_t* mk_page_table() { }

page_dir_entry_t get_entry(page_table_t* table)
{
    page_dir_entry_t entry;
    memsetb((byte*)&entry, 0, sizeof(page_dir_entry_t));
}

void switch_page_dir(page_dir_t* page_dir)
{
    pdpte_t first_pdpt = root_pdpt->directories[0];
    first_pdpt.dir = (qword)page_dir >> 12;
    flush_pages();
}

void flush_pages()
{
    qword addr = 0x1000;
    __asm volatile("movq %%rax, %%cr3" ::"a"(addr));
    qword cr0;
    __asm volatile("movq %%cr0, %%rax" : "=a"(cr0));
    cr0 = cr0 | (1 << 31);
    __asm volatile("movq %%rax, %%cr0" ::"a"(cr0));
}

void* alloc_page_struct()
{
    for (int i = 0; i < 158; i++) {
        if (!page_struct_table[i]) {
            page_struct_table[i] = true;
            return (void*)0x1000 + i * 0x1000;
        }
    }

    return NULL;
}

void free_page_struct(void* ptr)
{
    int index = ((qword)ptr >> 12) + 1;
    page_struct_table[index] = false;
}
