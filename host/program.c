/*
 * File: Atari-cart.c
 * Author: dgrubb
 * Date: 07/07/2017
 *
 * Mimics ROM space (that is, a game program).
 */

#include "program.h"

/* Cartridges are represented as arrays of bytes in their own
 * part of memory. We "load" a program by storing a pointer 
 * to the desired program data.
 */
static const uint8_t *program = 0;

inline void program_read(uint16_t address, uint8_t * data)
{
    if (program) {
        *data = program[address];
    }
}

inline void program_load(const uint8_t *cart)
{
    if (program) {
        program_eject();
    }
    program = cart;
}

inline void program_eject(void)
{
    /* Clear the pointer to the current program array */
    program = 0;
}

