/*
 * File: mos6502.h
 * Author: dgrubb
 * Date: 06/23/2017
 *
 * Provides implementations of the 6502 model.
 */

#ifndef _MOS6502_H
#define _MOS6502_H

#include <stdint.h>
#include "mos6502-opcodes.h"

typedef enum {
    MOS6502_STATUS_FLAG_NEGATIVE  = 0x80,
    MOS6502_STATUS_FLAG_OVERFLOW  = 0x40,
    MOS6502_STATUS_FLAG_BREAK     = 0x10,
    MOS6502_STATUS_FLAG_DECIMAL   = 0x08,
    MOS6502_STATUS_FLAG_INTERRUPT = 0x04,
    MOS6502_STATUS_FLAG_ZERO      = 0x02,
    MOS6502_STATUS_FLAG_CARRY     = 0x01
} mos6502_status_flag_t;

typedef enum {
    MOS6502_REG_A = 0,
    MOS6502_REG_Y,
    MOS6502_REG_X,
    MOS6502_REG_PC,
    MOS6502_REG_S,
    MOS6502_REG_P
} mos6502_register_t;

typedef struct {
    /* Internal registers */
    uint8_t  A;   /* Accumulator */
    uint8_t  Y;   /* Y register */
    uint8_t  X;   /* X register */
    uint16_t PC;  /* Program counter */
    uint8_t  S;   /* Stack pointer */
    uint8_t  P;   /* Status register */
    /* State description */
    uint8_t       current_instruction; /* Current op-code and addressing mode */
    uint8_t       current_clock;       /* Current clock tick of the current instruction */
    uint16_t      address_bus;         /* Address bus */
    uint8_t       data_bus;            /* Data bus */
} mos6502;

void mos6502_init(void);
void mos6502_reset(void);
void mos6502_clock_tick(void);
void mos6502_set_register(mos6502_register_t reg, uint8_t value);
void mos6502_get_register(mos6502_register_t reg, uint8_t *value);
void mos6502_set_address_bus_hl(uint8_t adh, uint8_t adl);
void mos6502_set_address_bus(uint16_t address);
void mos6502_get_address_bus(uint16_t *address);
void mos6502_set_data_bus(uint8_t data);
void mos6502_get_data_bus(uint8_t *data);
void mos6502_increment_PC(void);
uint16_t mos6502_get_PC(void);
void mos6502_set_PC(uint16_t pc);
void mos6502_set_PC_hl(uint8_t pch, uint8_t pcl);
void mos6502_set_status_flag(mos6502_status_flag_t flag, int value);
int mos6502_get_status_flag(mos6502_status_flag_t flag);
char * mos6502_get_register_str(mos6502_register_t reg);
void mos5607_get_current_instruction(uint8_t *instruction);
void mos5607_get_current_instruction_cycle(uint8_t *instruction_cycle);

#endif /* _MOS6502_H */
