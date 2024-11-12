# Building the Eth OS

## Prerequisites
Install the following dependencies:

- NASM
- GCC/Clang
- GRUB
- GNU Make
- DOS FS Tools
- MTOOLS

## Arch Linux
One command to install all the dependencies:

```
sudo pacman -S nasm grub mtools dosfstools gcc clang make
```

NOTE: If you get this error:
```
grub-mkrescue: error: xorriso not found
make: *** [grub-mkrescue] Error 1
```
Then you need to install xorriso which is required for grub-mkrescue to create the ISO image:
```
sudo pacman -S xorriso
```
## Ubuntu
One command to install all the dependencies:

```
sudo apt install nasm grub mtools dosfstools gcc clang make
```

## Fedora
One command to install all the dependencies:

```
sudo dnf install nasm grub mtools dosfstools gcc clang make
```

# Building the ISO

## Build the ISO

```
make
```

## Build the ISO and RUN in QEMU

```
make run
```
