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

#define ATA_PRIMARY_IO 0x1F0
#define ATA_SECONDARY_IO 0x170

void init_ata();

bool select_ata(uint16_t port, bool master);
bool ata_identify();
bool ata_poll();

bool ata_read_block(uint16_t* buffer, uint32_t lba);
bool ata_write_block(uint16_t* buffer, uint32_t lba);

bool ata_read(uint16_t* buffer, uint32_t lba, uint32_t count);
bool ata_write(uint16_t* buffer, uint32_t lba, uint32_t count);


#endif // #ifndef ATA_H
