# name of your application
APPLICATION = STM32-RIOT-6502

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-f446

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/..

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP
#CFLAGS += -Wno-unused-parameter

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 0

DISABLE_MODULE += core_msg
USEMODULE += xtimer

FEATURES_REQUIRED += periph_timer

export INCLUDES += -I$(CURDIR)

CFLAGS += -DPRINT_STATE
CFLAGS += -DMANUAL_STEP

BIN_DIRS += atari
BIN_DIRS += mos6502
BIN_DIRS += mos6532
BIN_DIRS += test
BIN_USEMODULE += host
BIN_USEMODULE += mos6502
BIN_USEMODULE += mos6532
BIN_USEMODULE += test
BIN_USEMODULE += STM32-RIOT-6502    # include application module (named $APPLICATION)

include $(RIOTBASE)/Makefile.include
