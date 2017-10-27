/*
 * File: memmap.h
 * Author: dgrubb
 * Date: 06/28/2017
 *
 * Delegates access to memory mapped devices.
 */

#ifndef _MEMMAP_H
#define _MEMMAP_H

#include <stdint.h>

#define MEMMAP_RAM_START 0x0080U
#define MEMMAP_RAM_END   0x02FFU
#define MEMMAP_ROM_START 0x1000U
#define MEMMAP_ROM_END   0x1FFFU

void memmap_write(void);
void memmap_read(uint8_t *data);
void memmap_map_address(uint16_t *address);

#endif /* _MEMMAP_H */
