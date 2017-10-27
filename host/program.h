/*
 * File: Atari-cart.h
 * Author: dgrubb
 * Date: 07/07/2017
 *
 * Mimics ROM space (that is, a game program).
 */

#ifndef _PROGRAM_H
#define _PROGRAM_H

#include <stdint.h>

void program_read(uint16_t address, uint8_t * data);
void program_load(const uint8_t *cart);
void program_eject(void);

#endif /* _PROGRAM_H */
