# Eth-OS Community Edition
<div align="center">

<img src="./.github/imgs/os-screenshot.png" />

![Badge Workflow](https://github.com/ethanprogramser/eth-os-com/actions/workflows/ci.yml/badge.svg)
![Github Last Commit](https://img.shields.io/github/last-commit/ethanprogramser/eth-os-com)
![Github Contributors](https://img.shields.io/github/contributors/ethanprogramser/eth-os-com)
![GitHub Repo stars](https://img.shields.io/github/stars/ethanprogramser/eth-os-com)

</div>

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
* GCC/Clang
* GRUB
* GNU Make
* DOS FS Tools
* MTools

## Arch linux
Install with one command using pacman

``` bash
pacman -S nasm gcc grub make dosfstools mtools qemu
```
One by one

```bash
# Install NASM (Netwide Assembler)
sudo pacman -S nasm

# Install GCC (GNU Compiler Collection)
sudo pacman -S gcc

# Install Clang (LLVM compiler)
sudo pacman -S clang

# Install GRUB (GRand Unified Bootloader)
sudo pacman -S grub

# Install GNU Make (build automation tool)
sudo pacman -S make

# Install DOS FS Tools (tools for managing DOS filesystems)
sudo pacman -S dosfstools

# Install MTools (utilities for manipulating MS-DOS filesystems)
sudo pacman -S mtools
```

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

# Contributors wall
![list of conributors](https://contrib.rocks/image?repo=ethanprogramser/eth-os-com)
