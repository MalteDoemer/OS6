#include "kernel.h"

bool page_struct_table[158];

pdpt_t* pdpt;
page_table_t* kernel_page_table1;
page_table_t* kernel_page_table2;

void init_paging()
{
    page_struct_table[0] = true;
    page_struct_table[1] = true;
    page_struct_table[2] = true;
    page_struct_table[3] = true;
    page_struct_table[4] = true;

    pdpt = (pdpt_t*)0x2000;
    kernel_page_table1 = (page_table_t*)0x4000;
    kernel_page_table2 = (page_table_t*)0x5000;

    page_dir_t* test = make_page_dir();
    page_map(test, 0x400000, 0x400000);
    page_map(test, 0x600000, 0x600000);
    set_activ_dir(test);

    byte* b = ((byte*)0x600000);
    *b = 36;

    set_activ_dir((page_dir_t*)0x3000);
    free_page_dir(test);
}

page_dir_t* make_page_dir()
{
    page_dir_t* dir = alloc_page_struct();
    memsetb((byte*)dir, 0, sizeof(page_dir_t));

    dir->entries[0].p = 1;
    dir->entries[0].rw = 1;
    dir->entries[0].table = (qword)kernel_page_table1 >> 12;

    dir->entries[1].p = 1;
    dir->entries[1].rw = 1;
    dir->entries[1].table = (qword)kernel_page_table2 >> 12;

    return dir;
}

void free_page_dir(page_dir_t* dir)
{
    for (int i = 2; i < 512; i++)
        if (dir->entries[i].p)
            free_page_struct((void*)(dir->entries[i].table << 12));
    free_page_struct(dir);
}

void page_map(page_dir_t* dir, qword phys, qword virt)
{
    short id = virt >> 21;
    page_table_t* table = alloc_page_struct();

    dir->entries[id].table = (qword)table >> 12;
    dir->entries[id].p = 1;
    dir->entries[id].rw = 1;

    for (int i = 0; i < 512; i++) {
        table->pages[i].frame = phys >> 12;
        table->pages[i].p = 1;
        table->pages[i].rw = 1;
        phys += 4096;
    }
}

void page_map_user(page_dir_t* dir, qword phys, qword virt)
{
    short id = virt >> 21;
    page_table_t* table = alloc_page_struct();

    dir->entries[id].table = (qword)table >> 12;
    dir->entries[id].p = 1;
    dir->entries[id].rw = 1;
    dir->entries[id].us = 1;

    for (int i = 0; i < 512; i++) {
        table->pages[i].frame = phys >> 12;
        table->pages[i].p = 1;
        table->pages[i].rw = 1;
        table->pages[i].us = 1;
        phys += 4096;
    }
}

void set_activ_dir(page_dir_t* dir)
{
    pdpte_t entry;
    memsetq((qword*)&entry, 0, 1);

    entry.p = 1;
    entry.rw = 1;
    entry.dir = (qword)dir >> 12;

    pdpt->directories[0] = entry;
    flush_pages();
}

void* alloc_page_struct()
{
    for (int i = 0; i < 158; i++) {
        if (!page_struct_table[i]) {
            page_struct_table[i] = true;
            byte* addr = (byte*)(0x1000 + i * 0x1000);
            memsetb(addr, 0, 0x1000);
            return (void*)addr;
        }
    }

    return NULL;
}

void free_page_struct(void* ptr)
{
    int index = ((qword)ptr >> 12) - 1;
    page_struct_table[index] = false;
}
