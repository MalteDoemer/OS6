#include "kernel.h"

volatile uint8_t keystates[0x80];
volatile uint8_t scancode;

void init_keyboard() { register_isr(0x21, keyboard_handler); }

#define SHIFT_DOWN (keystates[SC_LEFT_SHIFT] || keystates[SC_RIGHT_SHIFT])
#define CTRL_DOWN (keystates[SC_LEFT_CTRL])
#define ALT_DOWN (keystates[SC_LEFT_ALT])

uint8_t read_char()
{
wait_for_char:
    while (scancode == 0 || scancode > 0x80)
        hlt();

    if (CTRL_DOWN || ALT_DOWN && SHIFT_DOWN)
        goto wait_for_char;

    uint8_t chr;

    if (SHIFT_DOWN)
        chr = KEYMAP[scancode + SHIFT_OFFSET];
    else if (ALT_DOWN)
        chr = KEYMAP[scancode + ALT_OFFSET];
    else
        chr = KEYMAP[scancode];

    scancode = 0;
    return chr;
}

void keyboard_handler(cpu_state_t* stack)
{
    uint8_t status = inb(0x64);

    if (status & 1) {
        scancode = inb(0x60);

        if (scancode > 0x80)
            keystates[scancode - 0x80] = 0;
        else
            keystates[scancode] = 1;
    }

    outb(0x20, 0x20);
}