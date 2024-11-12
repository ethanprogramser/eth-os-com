# Building the Eth OS

## Tools and Packages
Install the following dependencies:

- NASM
- GCC/Clang
- GRUB
- GNU Make
- DOS FS Tools
- MTools
- GNU xorriso

Optional:
- [compiledb](https://github.com/nickdiego/compiledb) (to generate
`compile_commands.json` for clangd)

### Arch Linux
``` sh
sudo pacman -S nasm grub mtools dosfstools gcc make xorriso
```

### Ubuntu
``` sh
sudo apt install nasm grub mtools dosfstools gcc make xorriso
```

### Fedora
``` sh
sudo dnf install nasm grub mtools dosfstools gcc make xorriso
```

## Building the ISO
``` sh
# Build ISO
make

# Build ISO and run QEMU
make run

# Build release ISO
make release

# OR (with `compile_commands.json' generation)
./compile.sh

./compile_and_run.sh
```
