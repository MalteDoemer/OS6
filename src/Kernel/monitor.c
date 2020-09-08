#include "kernel.h"

word cursor_pos;
byte vga_attrib;
volatile word *vga_buffer;

byte ansi_to_screen[256] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    '\b',
    '\t',
    '\n',
    '\v',
    '\f',
    '\r',
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    '\e',
    0,
    0,
    0,
    0,
    ' ',
    '!',
    '"',
    '#',
    '$',
    '%',
    '&',
    '\'',
    '(',
    ')',
    '*',
    '+',
    ',',
    '-',
    '.',
    '/',
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    ':',
    ';',
    '<',
    '=',
    '>',
    '?',
    '@',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F',
    'G',
    'H',
    'I',
    'J',
    'K',
    'L',
    'M',
    'N',
    'O',
    'P',
    'Q',
    'R',
    'S',
    'T',
    'U',
    'V',
    'W',
    'X',
    'Y',
    'Z',
    '[',
    '\\',
    ']',
    '^',
    '_',
    '`',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z',
    '{',
    '|',
    '}',
    '~',
    0,
    0,   // €
    0,   //
    0,   // ‚
    159, // ƒ
    0,   // „
    0,   // …
    0,   // †
    0,   // ‡
    0,   // ˆ
    0,   // ‰
    0,   // Š
    0,   // ‹
    0,   // Œ
    0,   //
    0,   // Ž
    0,   //
    0,   //
    0,   // ‘
    0,   // ’
    0,   // “
    0,   // ”
    0,   // •
    0,   // –
    0,   // —
    0,   // ˜
    0,   // ™
    0,   // š
    0,   // ›
    0,   // œ
    0,   //
    0,   // ž
    0,   // Ÿ
    0,   //
    173, // ¡
    155, // ¢
    156, // £
    0,   // ¤
    157, // ¥
    '|', // ¦
    22,  // §
    0,   // ¨
    0,   // ©
    166, // ª
    174, // «
    170, // ¬
    0,   // ­
    0,   // ®
    0,   // ¯
    248, // °
    241, // ±
    254, // ²
    0,   // ³
    0,   // ´
    230, // µ
    0,   // ¶
    249, // ·
    0,   // ¸
    0,   // ¹
    167, // º
    175, // »
    172, // ¼
    171, // ½
    0,   // ¾
    168, // ¿
    0,   // À
    0,   // Á
    0,   // Â
    0,   // Ã
    142, // Ä
    143, // Å
    146, // Æ
    128, // Ç
    0,   // È
    144, // É
    0,   // Ê
    0,   // Ë
    0,   // Ì
    0,   // Í
    0,   // Î
    0,   // Ï
    0,   // Ð
    165, // Ñ
    0,   // Ò
    0,   // Ó
    0,   // Ô
    0,   // Õ
    153, // Ö
    0,   // ×
    0,   // Ø
    0,   // Ù
    0,   // Ú
    0,   // Û
    154, // Ü
    0,   // Ý
    0,   // Þ
    0,   // ß
    133, // à
    160, // á
    131, // â
    0,   // ã
    132, // ä
    134, // å
    0,   // æ
    135, // ç
    138, // è
    130, // é
    136, // ê
    137, // ë
    141, // ì
    161, // í
    140, // î
    139, // ï
    0,   // ð
    164, // ñ
    149, // ò
    162, // ó
    147, // ô
    0,   // õ
    148, // ö
    246, // ÷
    237, // ø
    151, // ù
    163, // ú
    150, // û
    129, // ü
    0,   // ý
    0,   // þ
    152, // ÿ
};

void init_vga()
{
    cursor_pos = 0;
    vga_attrib = 0x1F;
    vga_buffer = (volatile word *)0xB8000;
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
    if (cursor_pos >= VGA_CHARS)
    {
        for (int i = 0; i < VGA_CHARS - VGA_WIDTH; i++)
            vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
        for (int i = VGA_CHARS - VGA_WIDTH; i < VGA_CHARS; i++)
            vga_buffer[i] = (vga_attrib << 8) | ' ';
        cursor_pos = (cursor_pos / VGA_WIDTH) * VGA_WIDTH;
        vga_update_cursor();
    }
}

void vga_putc(byte c)
{
    if (c == '\b' && cursor_pos)
        cursor_pos--;
    else if (c == '\t')
        cursor_pos = (cursor_pos + 4) & ~(4 - 1);
    else if (c == '\r')
        cursor_pos = (cursor_pos / VGA_WIDTH) * VGA_WIDTH;
    else if (c == '\n')
    {
        cursor_pos += VGA_WIDTH;
#ifdef LF_LINE_END
        cursor_pos = (cursor_pos / VGA_WIDTH) * VGA_WIDTH;
#endif
    }
    else if (c >= ' ')
    {
        vga_buffer[cursor_pos] = (vga_attrib << 8) | ansi_to_screen[c];
        cursor_pos++;
    }

    vga_scroll();
    vga_update_cursor();
}

void vga_puts(byte *str)
{
    while (*str)
    {
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

void vga_copy(word *buffer, size_t length)
{
    memcpyw(vga_buffer, buffer, length);
}

void vga_puth(dword num)
{
    static const byte *pattern = "0123456789ABCDEF";

    vga_putc('0');
    vga_putc('x');

    for (int i = 28; i > -1; i -= 4)
        vga_putc(pattern[(num >> i) & 0xF]);
}