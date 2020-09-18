#include "kernel.h"

uint16_t port;
bool master;

void init_ata()
{
    select_ata(ATA_PRIMARY_IO, true);
    ata_identify();

    select_ata(ATA_PRIMARY_IO, false);
    ata_identify();

    select_ata(ATA_SECONDARY_IO, true);
    ata_identify();

    select_ata(ATA_SECONDARY_IO, false);
    ata_identify();
}

bool select_ata(uint16_t _port, bool _master)
{
    if (!(_port == ATA_PRIMARY_IO || _port == ATA_SECONDARY_IO))
        return false;

    port = _port;
    master = _master;

    return true;
}

bool ata_identify()
{
    outb(port + ATA_DEVICE, master ? 0xA0 : 0xB0);
    outb(port + ATA_CTRL, 0);

    outb(port + ATA_DEVICE, 0xA0);

    if (inb(port + ATA_CMD) == 0xFF)
        return false; // Device is not present

    outb(port + ATA_DEVICE, master ? 0xA0 : 0xB0);
    outb(port + ATA_SECTOR, 0);
    outb(port + ATA_LBA_LOW, 0);
    outb(port + ATA_LBA_MID, 0);
    outb(port + ATA_LBA_HIGH, 0);
    outb(port + ATA_CMD, 0xEC); // Identify command

    if (!ata_poll())
        return false;

    uint16_t ata_info[256];

    for (int i = 0; i < 256; i++)
        ata_info[i] = inw(port + ATA_DATA);

    return true;
}

bool ata_poll()
{
    uint8_t status = inb(port + ATA_CMD);

    if (status == 0x00)
        return false;

    while (((status & 0x80) == 0x80) && ((status & 0x01) != 0x01))
        status = inb(port + ATA_CMD);

    if (status & 0x01)
        return false;

    return true;
}

bool ata_read_block(uint16_t* buffer, uint32_t lba)
{
    outb(port + ATA_DEVICE, (master ? 0xE0 : 0xF0) | (lba >> 24 & 0x0F));
    outb(port + ATA_ERROR, 0);
    outb(port + ATA_SECTOR, 1);

    outb(port + ATA_LBA_LOW, lba & 0xFF);
    outb(port + ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(port + ATA_LBA_HIGH, (lba >> 16) & 0xFF);

    outb(port + ATA_CMD, 0x20);

    if (!ata_poll())
        return false;

    for (uint32_t i = 0; i < 256; i++)
        buffer[i] = inw(port + ATA_DATA);

    return true;
}

bool ata_write_block(uint16_t* buffer, uint32_t lba)
{
    outb(port + ATA_DEVICE, (master ? 0xE0 : 0xF0) | (lba >> 24 & 0x0F));
    outb(port + ATA_ERROR, 0);
    outb(port + ATA_SECTOR, 1);

    outb(port + ATA_LBA_LOW, lba & 0xFF);
    outb(port + ATA_LBA_MID, (lba >> 8) & 0xFF);
    outb(port + ATA_LBA_HIGH, (lba >> 16) & 0xFF);

    outb(port + ATA_CMD, 0x30);

    ata_poll();

    for (uint32_t i = 0; i < 256; i++)
        outw(port + ATA_DATA, buffer[i]);
}

bool ata_read(uint16_t* buffer, uint32_t lba, uint32_t count)
{
    for (; count; count--) {
        ata_read_block(buffer, lba);
        buffer += 256;
        lba++;
    }
}

bool ata_write(uint16_t* buffer, uint32_t lba, uint32_t count)
{
    for (; count; count--) {
        ata_write_block(buffer, lba);
        buffer += 256;
        lba++;
    }
}
