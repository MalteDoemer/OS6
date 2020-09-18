#ifndef ATA_H
#define ATA_H

#include "kernel.h"

#define ATA_DATA 0x0
#define ATA_ERROR 0x1
#define ATA_SECTOR 0x2
#define ATA_LBA_LOW 0x3
#define ATA_LBA_MID 0x4
#define ATA_LBA_HIGH 0x5
#define ATA_DEVICE 0x6
#define ATA_CMD 0x7
#define ATA_CTRL 0x206

typedef struct ata_t {
    uint16_t base_port;
    bool master;
} ata_t;

void ata_identify(ata_t* ata);
void ata_read_28(ata_t* ata, uint32_t sector_num, uint32_t count);
void ata_write_28(ata_t* ata, uint32_t sector_num, uint8_t* data, uint32_t count);
void ata_flush(ata_t* ata);

#endif // #ifndef ATA_H
