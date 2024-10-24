# Eth-OS Community Edition
<img src="./.github/imgs/os-screenshot.png" />
![GitHub last commit](https://img.shields.io/github/last-commit/ethanprogramser/eth-os-com)


Community driven 32-bit OS based on
[Eth-OS](https://github.com/ethanprogramser/eth-os).

__Eth-OS__ is being created in the
[programming everyday](https://www.youtube.com/watch?v=fyZ0Gs9W194&list=PL29dTm11fF9QNI7_xIxwjcaLFCeNhaCym&pp=iAQB)
youtube series by [eprograms](https://www.youtube.com/@eprograms).

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
Tools:
* NASM
* C compiler
* GRUB
* xorriso
* GNU Make
* MTools

Optional:
* [compiledb](https://github.com/nickdiego/compiledb) (to generate
  `compile_commands.json` for clangd)

To run you need `qemu` installed.

``` sh
# To compile OS and make .iso image.
make

# To compile OS and run it.
make run

# To clean-up
make clean

# OR (needs compiledb)
# This variant generates `compile_commands.json` for clangd
./compile.sh

./compile_and_run.sh

./clean.sh
```
