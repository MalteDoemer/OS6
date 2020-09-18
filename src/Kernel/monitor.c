#include "kernel.h"

uint16_t cursor;
uint8_t vga_attrib;
uint16_t* vga_buffer;

void init_vga()
{
    cursor = 0;
    vga_attrib = 0x1F;
    vga_buffer = (uint16_t*)0xB8000;
    vga_clear();
}

void vga_update_cursor()
{
    outb(0x3D4, 14);
    outb(0x3D5, cursor >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor);
}

void vga_scroll()
{
    if (cursor >= VGA_CHARS) {
        memcpyw(vga_buffer, vga_buffer + VGA_WIDTH, VGA_CHARS - VGA_WIDTH);
        memsetw(vga_buffer + (VGA_CHARS - VGA_WIDTH), (vga_attrib << 8) | ' ', VGA_WIDTH);
        cursor = VGA_CHARS - VGA_WIDTH;
        vga_update_cursor();
    }
}

void vga_putc(uint8_t c)
{
    if (c == 0)
        return;
    if (c == '\b' && cursor) {
        cursor--;
        vga_buffer[cursor] = (vga_attrib << 8) | ' ';
    } else if (c == '\t')
        cursor = (cursor + 4) & ~(4 - 1);
    else if (c == '\r')
        cursor = (cursor / VGA_WIDTH) * VGA_WIDTH;
    else if (c == '\n') {
        cursor += VGA_WIDTH;
        cursor = (cursor / VGA_WIDTH) * VGA_WIDTH;
    } else if (c >= ' ') {
        vga_buffer[cursor] = (vga_attrib << 8) | ansi_to_vga[c];
        cursor++;
    }

    vga_scroll();
    vga_update_cursor();
}

void vga_puts(uint8_t* str)
{
    while (*str) {
        vga_putc(*str);
        str++;
    }
}

void vga_clear()
{
    cursor = 0;
    memsetw(vga_buffer, (vga_attrib << 8) | ' ', VGA_CHARS);
    vga_update_cursor();
}

void vga_copy(uint16_t* buffer) { memcpyw(vga_buffer, buffer, VGA_CHARS); }

void vga_puth(duint16_t num)
{
    static const uint8_t* pattern = "0123456789ABCDEF";

    vga_putc('0');
    vga_putc('x');

    for (int i = 28; i > -1; i -= 4)
        vga_putc(pattern[(num >> i) & 0xF]);
}