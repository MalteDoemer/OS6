#ifndef GDT_H
#define GDT_H

#include "kernel.h"

#define KERNEL_CODE (0x08 | 0b000)
#define KERNEL_DATA (0x10 | 0b000)
#define USER_CODE (0x18 | 0b011)
#define USER_DATA (0x20 | 0b011)
#define TSS_ENTRY (0x28 | 0b011)

typedef struct tss_t {
    duint16_t r1;
    quint16_t rsp0;
    quint16_t rsp1;
    quint16_t rsp2;
    quint16_t r2;
    quint16_t ist1;
    quint16_t ist2;
    quint16_t ist3;
    quint16_t ist4;
    quint16_t ist5;
    quint16_t ist6;
    quint16_t ist7;
    quint16_t r3;
    uint16_t r4;
    uint16_t IOPB;
} __attribute__((__packed__)) tss_t;

typedef struct gdt_seg_desc_t {
    quint16_t : 40;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t : 1;
    uint8_t cd : 1;
    uint8_t s : 1;
    uint8_t dpl : 2;
    uint8_t p : 1;
    uint8_t : 5;
    uint8_t l : 1;
    uint16_t : 10;
} __attribute__((__packed__)) gdt_seg_desc_t;

typedef struct gdt_tss_desc_t {
    uint16_t limit;
    duint16_t base_low : 24;
    uint8_t type : 4;
    uint8_t : 1;
    uint8_t dpl : 2;
    uint8_t p : 1;
    uint8_t : 8;
    uint8_t : 4;
    quint16_t base_high : 40;
    duint16_t : 32;
} __attribute__((__packed__)) gdt_tss_desc_t;

typedef struct gdt_t {
    gdt_seg_desc_t null_desc;
    gdt_seg_desc_t kernel_code;
    gdt_seg_desc_t kernel_data;
    gdt_seg_desc_t user_code;
    gdt_seg_desc_t user_data;
    gdt_tss_desc_t tss_desc;
} __attribute__((__packed__)) gdt_t;

/* Initializes the Global Descriptor Table */
void init_gdt();

/* Function defined in assembly.asm to load the gdt */
void load_gdt(uint16_t limit, quint16_t base);

/* Set an entry in the Global Descriptor Table */
void set_gdt_seg(gdt_seg_desc_t* desc, uint8_t dpl, bool code);

/* Writes a tss entry into the gdt */
void set_gdt_tss(gdt_tss_desc_t* desc, uint8_t dpl, quint16_t base, uint16_t limit);

/* Function defined in assembly.asm to reload the tss */
void load_tss(uint16_t tss_entry);

/* Sets rsp0 in the tss data structure */
void set_kernel_stack(quint16_t rsp);

#endif // #ifndef GDT_H
