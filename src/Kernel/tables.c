#include "kernel.h"

uint8_t ansi_to_vga[256] = {
    0, 0, 0, 0, 0, 0, 0, 0, '\b', '\t', '\n', '\v', '\f', '\r', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\e', 0, 0, 0, 0,
    ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{',
    '|', '}', '~', 0,
    0, // €
    0, //
    0, // ‚
    159, // ƒ
    0, // „
    0, // …
    0, // †
    0, // ‡
    0, // ˆ
    0, // ‰
    0, // Š
    0, // ‹
    0, // Œ
    0, //
    0, // Ž
    0, //
    0, //
    0, // ‘
    0, // ’
    0, // “
    0, // ”
    0, // •
    0, // –
    0, // —
    0, // ˜
    0, // ™
    0, // š
    0, // ›
    0, // œ
    0, //
    0, // ž
    0, // Ÿ
    0, //
    173, // ¡
    155, // ¢
    156, // £
    0, // ¤
    157, // ¥
    '|', // ¦
    22, // §
    0, // ¨
    0, // ©
    166, // ª
    174, // «
    170, // ¬
    0, // ­
    0, // ®
    0, // ¯
    248, // °
    241, // ±
    254, // ²
    0, // ³
    0, // ´
    230, // µ
    0, // ¶
    249, // ·
    0, // ¸
    0, // ¹
    167, // º
    175, // »
    172, // ¼
    171, // ½
    0, // ¾
    168, // ¿
    0, // À
    0, // Á
    0, // Â
    0, // Ã
    142, // Ä
    143, // Å
    146, // Æ
    128, // Ç
    0, // È
    144, // É
    0, // Ê
    0, // Ë
    0, // Ì
    0, // Í
    0, // Î
    0, // Ï
    0, // Ð
    165, // Ñ
    0, // Ò
    0, // Ó
    0, // Ô
    0, // Õ
    153, // Ö
    0, // ×
    0, // Ø
    0, // Ù
    0, // Ú
    0, // Û
    154, // Ü
    0, // Ý
    0, // Þ
    0, // ß
    133, // à
    160, // á
    131, // â
    0, // ã
    132, // ä
    134, // å
    0, // æ
    135, // ç
    138, // è
    130, // é
    136, // ê
    137, // ë
    141, // ì
    161, // í
    140, // î
    139, // ï
    0, // ð
    164, // ñ
    149, // ò
    162, // ó
    147, // ô
    0, // õ
    148, // ö
    246, // ÷
    237, // ø
    151, // ù
    163, // ú
    150, // û
    129, // ü
    0, // ý
    0, // þ
    152, // ÿ
};

uint8_t swiss_keymap[270] = {
    // Normal
    0,
    0,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '\'',
    '^',
    '\b',
    '\t',
    'q',
    'w',
    'e',
    'r',
    't',
    'z',
    'u',
    'i',
    'o',
    'p',
    0xFC,
    0xA8,
    '\n',
    0,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    0xF6,
    0xE4,
    0xA7,
    0,
    '$',
    'y',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '-',
    0,
    0,
    0,
    ' ',
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
    0,
    0,
    '<',
    0,
    0,
    0,

    // Shift

    0,
    0,
    '+',
    '"',
    '*',
    0xE7,
    '%',
    '&',
    '/',
    '(',
    ')',
    '=',
    '?',
    '`',
    '\b',
    '\t',
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Z',
    'U',
    'I',
    'O',
    'P',
    0xE8,
    '!',
    '\n',
    0,
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    0xE9,
    0xDF,
    0xB0,
    0,
    0xA3,
    'Y',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    ';',
    ':',
    '_',
    0,
    0,
    0,
    ' ',
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
    0,
    0,
    '>',
    0,
    0,
    0,

    // Alt

    0,
    0,
    0xA6,
    '@',
    '#',
    0,
    0,
    0xAC,
    '|',
    0xA2,
    0,
    0,
    0xB4,
    '~',
    '\b',
    '\t',
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
    '[',
    ']',
    '\n',
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
    '{',
    0,
    0,
    '}',
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
    ' ',
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
    0,
    0,
    '\\',
    0,
    0,
    0,
};

