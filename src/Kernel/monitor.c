#include "kernel.h"

word cursor_pos;
byte vga_attrib;
word* vga_buffer;

void init_vga()
{
    cursor_pos = 0;
    vga_attrib = 0x1F;
    vga_buffer = (word*)0xB8000;
    vga_clear();
}

void vga_update_cursor()
{
    outb(0x3D4, 14);
    outb(0x3D5, cursor_pos >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_pos);
}

void vga_scroll()
{
    if (cursor_pos >= VGA_CHARS) {
        for (int i = 0; i < VGA_CHARS - VGA_WIDTH; i++)
            vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
        for (int i = VGA_CHARS - VGA_WIDTH; i < VGA_CHARS; i++)
            vga_buffer[i] = (vga_attrib << 8) | ' ';
        cursor_pos = VGA_CHARS - VGA_WIDTH;
        vga_update_cursor();
    }
}

void vga_putc(byte c)
{
    if (c == 0)
        return;
    if (c == '\b' && cursor_pos) {
        cursor_pos--;
        vga_buffer[cursor_pos] = (vga_attrib << 8) | ' ';
    } else if (c == '\t')
        cursor_pos = (cursor_pos + 4) & ~(4 - 1);
    else if (c == '\r')
        cursor_pos = (cursor_pos / VGA_WIDTH) * VGA_WIDTH;
    else if (c == '\n') {
        cursor_pos += VGA_WIDTH;
        cursor_pos = (cursor_pos / VGA_WIDTH) * VGA_WIDTH;
    } else if (c >= ' ') {
        vga_buffer[cursor_pos] = (vga_attrib << 8) | ansi_to_vga[c];
        cursor_pos++;
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
    cursor_pos = 0;
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