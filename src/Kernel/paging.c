#include "kernel.h"

bool page_struct_table[256];

qword memtop;

pdpt_t* pdpt;
page_dir_t* kernel_dir;
page_dir_t* current_dir;

void init_paging()
{
    memtop = MEM_TOP;
    /* map two 2 MBytes pages */
    pdpt = (pdpt_t*)0x2000;
    kernel_dir = make_page_dir();
    set_activ_dir(kernel_dir);
}

page_dir_t* make_page_dir()
{
    page_dir_t* dir = alloc_page_struct();

    /* kernel page 1 from 0 -> 0x200000 */
    dir->pages[0].p = 1;
    dir->pages[0].rw = 1;
    dir->pages[0].ps = 1;
    dir->pages[0].frame = 0x000000 >> 21;

    /* kernel page 2 from 0x200000 -> 0x400000 */
    dir->pages[1].p = 1;
    dir->pages[1].rw = 1;
    dir->pages[1].ps = 1;
    dir->pages[1].frame = 0x200000 >> 21;

    return dir;
}

void map_page(page_dir_t* dir, qword virt, qword phys, bool rw, bool us, bool xd)
{
    word id = virt >> 21;
    dir->pages[id].p = 1;
    dir->pages[id].ps = 1;
    dir->pages[id].frame = phys >> 21;

    dir->pages[id].rw = rw;
    dir->pages[id].us = us;
    dir->pages[id].xd = xd;
}

void set_activ_dir(page_dir_t* dir)
{
    if (current_dir == dir)
        return;
    current_dir = dir;

    pdpte_t entry;
    memsetq(&entry, 0, 1);

    entry.p = 1;
    entry.rw = 1;
    entry.dir = (qword)dir >> 12;

    pdpt->directories[0] = entry;
    flush_pages();
}

void* alloc_page_struct()
{
    for (qword i = 0; i < 256; i++) {
        if (!page_struct_table[i]) {
            page_struct_table[i] = true;
            void* addr = (void*)(PAGE_TABLE_BASE + i * 0x1000);
            memsetb(addr, 0, 0x1000);
            return addr;
        }
    }

    return NULL;
}

void free_page_struct(void* ptr)
{
    int index = ((qword)ptr >> 12) - 1;
    page_struct_table[index] = false;
}

qword allocate_page_frame()
{
    qword hold = memtop;
    memtop += PAGE_SIZE;
    return hold;
}

void free_page_frame(qword addr) { }
