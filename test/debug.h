/*
 * File: debug.h
 * Author: dgrubb
 * Date: 08/07/2017
 *
 * Provides helper functions for printing human-readable 
 * information.
 */

#ifndef _DEBUG_H
#define _DEBUG_H

#ifdef PRINT_STATE

#include "mos6502/mos6502.h"

typedef struct {
    uint8_t op;
    const char *str;
} debug_opcode_t;

void debug_print_status_flags(void);
void debug_print_memory_contents(uint16_t address);
void debug_print_special_register(mos6502_register_t reg);
void debug_print_buses(void);
void debug_print_execution_step(void);
int debug_get_status_flag(uint8_t flag);
void debug_print_instruction(void);
const char * debug_lookup_opcode_str(uint8_t opcode);

#endif /* PRINT_STATE */

#endif /* _DEBUG_H */
