TM1637 C library for STM8 MCUs
======

A library to configure and control TM1637 4-digit 7-segment display module. This library also contains the GPIO and CLK headers for STM8 MCUs.

Requirements
---

- STM8s MCU (STM8S103F3 is referenced in this code)
- STLink-V2 programmer module
- SDCC Compiler (**Do not** use the sdcc package from the Ubuntu repositories. Download the [latest version here](http://sdcc.sourceforge.net/snap.php))
- SDCC libraries (Use ``apt-get install sdcc-libraries`` on Linux)
- [stm8flash](https://github.com/vdudouyt/stm8flash) tool (Add this to the PATH or add the correct path the Makefile before building)

Build demo
---

``make clean``

``make``

``make flash`` (or ``make sudoflash`` in case superuser permissions are required to access stlink-v2)


Thanks
---

**vdudouyt** for the [stm8flash](https://github.com/vdudouyt/stm8flash) tool

**bitbank2** for the original [tm1637](https://github.com/bitbank2/tm1637) C library