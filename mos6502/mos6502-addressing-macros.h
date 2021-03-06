/* Bitwise calculation of whether two addresses
 * are on the same page. Courtesy of stella, emucode/MOS6502.m4:28
 */
#define NOT_SAME_PAGE(_addr1, _addr2) (((_addr1) ^ (_addr2)) & 0xFF00)

#define CALC_BRANCH() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&offset); \
            if (!condition) { \
                END_OPCODE(); \
                return 0; \
            } \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            addr = mos6502_get_PC() + offset; \
            if (NOT_SAME_PAGE(mos6502_get_PC(), addr)) { \
                return -1; \
            } \
            mos6502_set_PC(addr); \
            break; \
        case 3: \
            addr = 0xFF & (mos6502_get_PC() + offset); \
            mos6502_set_PC_hl((mos6502_get_PC() >> 8), addr); \
        default: \
            break; \
    } \

/*
 */
#define FETCH_STORE_ADDRESS_ABSOLUTE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adh); \
            return -1; \
        case 3: \
            mos6502_set_address_bus_hl(adh, adl); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_IMMEDIATE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ZERO_PAGE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, adl); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ABSOLUTE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adh); \
            return -1; \
        case 3: \
            mos6502_set_address_bus_hl(adh, adl); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_INDIRECT_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, (bal + X)); \
            memmap_read(&adl); \
            return -1; \
        case 4: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, ((bal + X) + 1)); \
            memmap_read(&adh); \
            return -1; \
        case 5: \
            mos6502_set_address_bus_hl(adh, adl); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ABSOLUTE_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bah); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            adl = bal + X; \
            if ((bal + X) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
            if (c) { \
                return -1; \
            } \
            break; \
        case 4: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            adl = bal + X; \
            if ((bal + X) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ABSOLUTE_Y_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bah); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
            if (c) { \
                return -1; \
            } \
            break; \
        case 4: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ZERO_PAGE_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, bal + X); \
        default: \
            break; \
    } \

#define FETCH_STORE_ADDRESS_ZERO_PAGE_Y_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            mos6502_set_address_bus_hl(0, bal + Y); \
        default: \
            break; \
    } \



/*
 * These macros apply when reading from a memory location prior
 * to perfroming an operation where the result is placed into, 
 * or occurs, entirely within the CPU (e.g., compare a value to 
 * the accumulator, or an index register etc.).
 */
#define FETCH_DATA_ABSOLUTE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adh); \
            return -1; \
        case 3: \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_IMMEDIATE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ZERO_PAGE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ABSOLUTE() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adl); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&adh); \
            return -1; \
        case 3: \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_INDIRECT_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, (bal + X)); \
            memmap_read(&adl); \
            return -1; \
        case 4: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, ((bal + X) + 1)); \
            memmap_read(&adh); \
            return -1; \
        case 5: \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_INDIRECT_Y_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&ial); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, ial); \
            memmap_read(&bal); \
            return -1; \
        case 3: \
            mos6502_set_address_bus_hl(0, ial+1); \
            memmap_read(&bah); \
            return -1; \
        case 4: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
            if (c) { \
                return -1; \
            } \
            break; \
        case 5: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ABSOLUTE_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bah); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            adl = bal + X; \
            if ((bal + X) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
            if (c) { \
                return -1; \
            } \
            break; \
        case 4: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            adl = bal + X; \
            if ((bal + X) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ABSOLUTE_Y_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bah); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
            if (c) { \
                return -1; \
            } \
            break; \
        case 4: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            adl = bal + Y; \
            if ((bal + Y) & 0x0100) { \
                c = 1; \
            } \
            adh = bah + c; \
            mos6502_set_address_bus_hl(adh, adl); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ZERO_PAGE_X_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_X, &X); \
            mos6502_set_address_bus_hl(0, bal + X); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA_ZERO_PAGE_Y_INDEXED() \
    switch(cycle) { \
        case 0: \
            return -1; \
        case 1: \
            mos6502_increment_PC(); \
            mos6502_set_address_bus(mos6502_get_PC()); \
            memmap_read(&bal); \
            return -1; \
        case 2: \
            mos6502_set_address_bus_hl(0, bal); \
            return -1; \
        case 3: \
            mos6502_get_register(MOS6502_REG_Y, &Y); \
            mos6502_set_address_bus_hl(0, bal + Y); \
            memmap_read(&data); \
        default: \
            break; \
    } \

#define FETCH_DATA() \
    if (OPCODE_ADDRESSING_MODE_IMMEDIATE == address_mode) { \
        FETCH_DATA_IMMEDIATE() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE == address_mode) { \
        FETCH_DATA_ZERO_PAGE() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE == address_mode) { \
        FETCH_DATA_ABSOLUTE() \
    } else if (OPCODE_ADDRESSING_MODE_INDIRECT_X_INDEXED == address_mode) { \
        FETCH_DATA_INDIRECT_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_INDIRECT_Y_INDEXED == address_mode) { \
        FETCH_DATA_INDIRECT_Y_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE_X_INDEXED == address_mode) { \
        FETCH_DATA_ABSOLUTE_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE_Y_INDEXED == address_mode) { \
        FETCH_DATA_ABSOLUTE_Y_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE_X_INDEXED == address_mode) { \
        FETCH_DATA_ZERO_PAGE_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE_Y_INDEXED == address_mode) { \
        FETCH_DATA_ZERO_PAGE_Y_INDEXED() \
    } \

#define FETCH_STORE_ADDRESS() \
    if (OPCODE_ADDRESSING_MODE_IMMEDIATE == address_mode) { \
        FETCH_STORE_ADDRESS_IMMEDIATE() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE == address_mode) { \
        FETCH_STORE_ADDRESS_ZERO_PAGE() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE == address_mode) { \
        FETCH_STORE_ADDRESS_ABSOLUTE() \
    } else if (OPCODE_ADDRESSING_MODE_INDIRECT_X_INDEXED == address_mode) { \
        FETCH_STORE_ADDRESS_INDIRECT_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE_X_INDEXED == address_mode) { \
        FETCH_STORE_ADDRESS_ABSOLUTE_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ABSOLUTE_Y_INDEXED == address_mode) { \
        FETCH_STORE_ADDRESS_ABSOLUTE_Y_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE_X_INDEXED == address_mode) { \
        FETCH_STORE_ADDRESS_ZERO_PAGE_X_INDEXED() \
    } else if (OPCODE_ADDRESSING_MODE_ZERO_PAGE_Y_INDEXED == address_mode) { \
        FETCH_STORE_ADDRESS_ZERO_PAGE_Y_INDEXED() \
    } \

