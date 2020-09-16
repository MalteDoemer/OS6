#include "kernel.h"

word cursor;
byte vga_attrib;
word* vga_buffer;

void init_vga()
{
    cursor = 0;
    vga_attrib = 0x1F;
    vga_buffer = (word*)0xB8000;
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
        for (int i = 0; i < VGA_CHARS - VGA_WIDTH; i++)
            vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
        for (int i = VGA_CHARS - VGA_WIDTH; i < VGA_CHARS; i++)
            vga_buffer[i] = (vga_attrib << 8) | ' ';
        cursor = VGA_CHARS - VGA_WIDTH;
        vga_update_cursor();
    }
}

void vga_putc(byte c)
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

void vga_puts(byte* str)
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

void vga_copy(word* buffer, size_t length) { memcpyw(vga_buffer, buffer, length); }

void vga_puth(dword num)
{
    static const byte* pattern = "0123456789ABCDEF";

    vga_putc('0');
    vga_putc('x');

    for (int i = 28; i > -1; i -= 4)
        vga_putc(pattern[(num >> i) & 0xF]);
}