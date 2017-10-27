/*
 * File: memmap.c
 * Author: dgrubb
 * Date: 06/28/2017
 *
 * Delegates access to memory mapped devices.
 */

#include "memmap.h"
#include "program.h"
#include "mos6502/mos6502.h"
#include "mos6532/mos6532.h"

#define IS_RAM(x) (x >= MEMMAP_RAM_START && x <= MEMMAP_RAM_END)
#define IS_ROM(x) (x >= MEMMAP_ROM_START && x <= MEMMAP_ROM_END)

inline void memmap_write(void)
{
    /* Fetch data and address from CPU */
    uint16_t address;
    uint8_t data;
    mos6502_get_data_bus(&data);
    mos6502_get_address_bus(&address);

    /* Access particular device */
    if (IS_RAM(address)) mos6532_write(address - MEMMAP_RAM_START, data);
    if (IS_ROM(address)) {
        /* Cartridges are read-only. Are there hardware peripherals which 
         * use this space for extending functionality? E.g., SuperCharger?
         */
    }
}

inline void memmap_read(uint8_t *data)
{
    /* Fetch address from CPU */
    uint16_t address;
    mos6502_get_address_bus(&address);

    /* Access particular device */
    if (IS_RAM(address)) mos6532_read(address - MEMMAP_RAM_START, data);
    if (IS_ROM(address)) program_read(address - MEMMAP_ROM_START, data);
}

