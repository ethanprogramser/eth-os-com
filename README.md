# Eth-OS Community Edition
<img src="./.github/imgs/os-screenshot.png" />

Community driven 32-bit OS based on
[Eth-OS](https://github.com/ethanprogramser/eth-os).

__Eth-OS__ is being created in the
[programming everyday](https://www.youtube.com/watch?v=fyZ0Gs9W194&list=PL29dTm11fF9QNI7_xIxwjcaLFCeNhaCym&pp=iAQB)
video series by [eprograms](https://www.youtube.com/@eprograms).

## TODO list
* [x] Boot process
* [x] VGA driver
* [x] GDT
* [x] Interrupts
* [x] Timer
* [x] Basic keyboard driver
* [ ] Shell
* [ ] Filesystem
* [ ] Standard library
* [ ] Basic GUI library
* [ ] Window manager
* [ ] Code editor

## Manual build
Dependencies:
* NASM
* C compiler
* GRUB
* xorriso
* GNU Make

To run you need `qemu` installed.

``` sh
# To compile OS and make .iso image and run OS.
make
```
