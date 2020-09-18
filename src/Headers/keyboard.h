#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "kernel.h"

#define SHIFT_OFFSET 90
#define ALT_OFFSET 180
#define KEYMAP swiss_keymap

enum SCAN_CODES {
    SC_ESCAPE = 0x01,
    SC_BACKSPACE = 0x0E,
    SC_ENTER = 0x1C,
    SC_LEFT_CTRL = 0x1D,
    SC_LEFT_SHIFT = 0x2A,
    SC_RIGHT_SHIFT = 0x36,
    SC_LEFT_ALT = 0x38,
    SC_SPACE = 0x39,
    SC_CAPS_LOCK = 0x3A,
    SC_F1 = 0x3B,
    SC_F2 = 0x3C,
    SC_F3 = 0x3D,
    SC_F4 = 0x3E,
    SC_F5 = 0x3F,
    SC_F6 = 0x40,
    SC_F7 = 0x41,
    SC_F8 = 0x42,
    SC_F9 = 0x43,
    SC_F10 = 0x44,
    SC_HOME = 0x47,
    SC_UP = 0x48,
    SC_PAGE_UP = 0x49,
    SC_LEFT = 0x4B,
    SC_RIGHT = 0x4D,
    SC_END = 0x4F,
    SC_PAGE_DOWN = 0x51,
    SC_INSERT = 0x52,
    SC_DELETE = 0x53,
    SC_F11 = 0x57,
    SC_F12 = 0x58,
};

void init_keyboard();

void keyboard_handler(cpu_state_t* stack);

uint8_t read_char();

#endif // #ifndef KEYBOARD_H
