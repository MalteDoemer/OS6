#include "kernel.h"

tss_t* tss;
gdt_t* gdt;

void init_gdt()
{
    tss = kmalloc(sizeof(tss_t));
    gdt = kmalloc(sizeof(gdt_t));

    memsetb(gdt, 0, sizeof(gdt_t));
    memsetb(tss, 0, sizeof(tss_t));

    set_gdt_seg(&gdt->kernel_code, 0, true);
    set_gdt_seg(&gdt->kernel_data, 0, false);
    set_gdt_seg(&gdt->user_code, 3, true);
    set_gdt_seg(&gdt->user_data, 3, false);
    set_gdt_tss(&gdt->tss_desc, 3, (qword)tss, sizeof(tss_t));

    tss->rsp0 = KERNEL_STACK;
    load_gdt(sizeof(gdt_t), (qword)gdt);
    flush_tss();
}

void set_gdt_seg(gdt_seg_desc_t* desc, byte dpl, bool code)
{
    desc->p = 1;
    desc->s = 1;
    desc->dpl = dpl;
    desc->cd = code;
    if (code)
        desc->l = 1;
}

void set_gdt_tss(gdt_tss_desc_t* desc, byte dpl, qword base, word limit)
{
    desc->dpl = dpl;
    desc->p = 1;
    desc->type = 0b1001;
    desc->limit = limit;
    desc->base_low = base & 0xFFFFFF;
    desc->base_high = (base >> 24) & 0xFFFFFFFFFF;
}

void set_kernel_stack(qword rsp) { tss->rsp0 = rsp; }