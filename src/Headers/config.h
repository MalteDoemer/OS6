#ifndef CONFIG_H
#define CONFIG_H

#define LF_LINE_END

#define KERNEL_STACK 0x1000

#define SLAVE_IRQS 0b11111111
#define MASTER_IRQS 0b11111011

#define KERNEL_CODE (0x08 | 0b000)
#define KERNEL_DATA (0x10 | 0b000)
#define USER_CODE (0x18 | 0b011)
#define USER_DATA (0x20 | 0b011)
#define TSS_ENTRY (0x28 | 0b011)

#endif // #ifndef CONFIG_H
