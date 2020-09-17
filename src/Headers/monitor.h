#ifndef MONITOR_H
#define MONITOR_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_CHARS (VGA_WIDTH * VGA_HEIGHT)

extern word cursor;
extern byte vga_attrib;
extern word* vga_buffer;

/* Initialize vga */
void init_vga();

/* Clear the screen with the current color */
void vga_clear();

/* Updates the Harware cursor */
void vga_update_cursor();

/* Scrolls if the cursor is at the end */
void vga_scroll();

/* Write a character at cursor position */
void vga_putc(byte c);

/* Write a string at cursor position */
void vga_puts(byte* str);

/* Write a 32-bit unsgined integer in hex format at cursor position */
void vga_puth(dword num);

/* Copy a buffer to video memory */
void vga_copy(word* buffer);

#endif // #ifndef MONITOR_H
