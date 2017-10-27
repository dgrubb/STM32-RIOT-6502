/*
 * File: mos6502-microcode.h
 * Author: dgrubb
 * Date: 06/27/2017
 *
 * Provides implementation of CPU logic without reference to
 * specific addressing modes.
 */

#ifndef _MOS6502_MICROCODE_H
#define _MOS6502_MICROCODE_H

#include <stdint.h>

void mos6502_ADC(uint8_t data);
void mos6502_AND(uint8_t data);
void mos6502_ASL(uint8_t *data);
void mos6502_ASL_Accumulator(void);
void mos6502_BIT(uint8_t data);
void mos6502_CMP(uint8_t data);
void mos6502_CPX(uint8_t data);
void mos6502_CPY(uint8_t data);
void mos6502_EOR(uint8_t data);
void mos6502_LSR(uint8_t *data);
void mos6502_LSR_Accumulator(void);
void mos6502_ORA(uint8_t *data);
void mos6502_ROL(uint8_t *data);
void mos6502_ROL_Accumulator(void);
void mos6502_ROR(uint8_t *data);
void mos6502_ROR_Accumulator(void);
void mos6502_SBC(uint8_t data);

#endif /* _MOS6502_MICROCODE_H */

