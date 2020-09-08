#ifndef MONITOR_H
#define MONITOR_H

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_CHARS VGA_WIDTH *VGA_HEIGHT

extern word cursor_pos;
extern byte vga_attrib;
extern volatile word *vga_buffer;
extern byte ansi_to_screen[256];

void init_vga();
void vga_clear();
void vga_update_cursor();
void vga_scroll();
void vga_putc(byte c);
void vga_puts(byte *str);
void vga_puth(dword num);
void vga_copy(word *buffer, size_t length);


#endif // #ifndef MONITOR_H
