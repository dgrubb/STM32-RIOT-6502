/*
 */

/* Standard library includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* RIOT includes */
#include "xtimer.h"
#include "timex.h"
#include "board.h"
#include "periph_conf.h"
#include "periph/gpio.h"

/* Atari and platform includes */
#include "mos6502/mos6502.h"
#include "host/program.h"
#include "mos6532/mos6532.h"
#ifdef EXEC_TESTS
    #include "test/test-carts.h"
    #include "test/tests.h"
#endif
#ifdef PRINT_STATE
    #include "test/debug.h"
#endif

static const char mos_logo[] = "\n\r"
"\n\r"
"                                 STM32-RIOT-6502\n\r"
"                                 ---------------\n\r"
"\n\r"
"                               by David Grubb, 2017\n\r"
"                    https://github.com/dgrubb/STM32-RIOT-6502\n\r"
"\n\r"                                                                              
"  ~MMMMMM  MM      NMI.            .=MMMMMI               ,ZOOOOOOOOOOOOOOOO8\n\r"
"  ~MMMMMM  MMMMM   NMMMM         MMMMMMMMMMMMM .       NMMMMMMMMMMMMMMMMMMMMM\n\r"
"  ~MMMMMM  MMMMMM  NMMMMM     .MMMMMMMMMMMMMMMMM.     MMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMM: NMMMMMM  .~MMMMMMMMMMMMMMMMMMMM   MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM. :MMMMMMMMMMMMMMMMMMMMMN..MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM. MMMMMMMMMMMMMMMMMMMMMMM..                       .\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM.$MMMMMMMMMMMMMMMMMMMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM.$MMMMMMMMMMMMMMMMMMMMMMMM.MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM. MMMMMMMMMMMMMMMMMMMMMMM                          \n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM. ,MMMMMMMMMMMMMMMMMMMMMD .MMMMMMMMMMMMMMMMMMMMMMMM\n\r"   
"  ~MMMMMM  MMMMMMM NMMMMMM.  :MMMMMMMMMMMMMMMMMMMD  .MMMMMMMMMMMMMMMMMMMMMMM\n\r"    
"  ~MMMMMM  MMMMMMM NMMMMMM.    MMMMMMMMMMMMMMMMM    .MMMMMMMMMMMMMMMMMMMMMMM\n\r"    
"  ~MMMMMM  MMMMMMM NMMMMMM.     .MMMMMMMMMMMMM      .MMMMMMMMMMMMMMMMMMMMM.\n\r"     
"  :MMMMMM  MMMMMMM NMMMMMM          =MMMMMI          ZZZZZZZZZZZZZZZZZ$\n\r"
"\n\r"
"                             Welcome to 1975!\n\r";

int main(void)
{
    puts(mos_logo);

    opcode_populate_ISA_table();
    mos6532_clear_memory();

    /* Emulation is ready to start so load program and reset CPU */
//    program_load();
    mos6502_reset();

    gpio_init(LED0_PIN, GPIO_OUT);

    while(1) {
#ifdef MANUAL_STEP
        getchar();
#endif
        gpio_toggle(LED0_PIN);
        mos6502_clock_tick();
    }

    return 0;
}
