# STM32-RIOT-2600

This project is a 6502 emulator specifically targeted at the STM32-F446 microcontroller, in particular using the [Nucleo-F446RE board](http://www.st.com/en/evaluation-tools/nucleo-f446re.html "Nucleo F446RE board"). Also included is a partial simulation of the MOS6532 (as used in the Atari 2600) to provide a small amount of RAM for executing programs.

The [RIOT OS](https://riot-os.org "RIOT OS") is used for configuring peripherals and managing device timing.

## Prerequisites

Requires an ARM toolchain:

* arm-none-eabi-gcc
* arm-none-eabi-gdb
* arm-none-eabi-binutils
* OpenOCD (programming utility)

On Debian/Ubuntu: 

```
$ sudo apt-get install gcc-arm-none-eabi gdb-arm-none-eabi openocd
```

## Build instructions

Checkout the RIOT OS operating system:

```
$ git clone --recursive https://github.com/RIOT-OS/RIOT.git
```

Enter the top-level directory of the RIOT project and checkout this project directly into it:

```
$ cd RIOT
$ git clone https://github.com/dgrubb/STM32-RIOT-6502.git
$ cd STM32-RIOT-6502
```

Make and flash to the target board as usual for a RIOT project:

```
$ make
$ make flash
$ make debug
```

A serial terminal will be available on (usually, your node may vary) /dev/ttyACM0:

```
$ screen /dev/ttyACM0 115200
```
