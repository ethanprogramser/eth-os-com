#ifndef __K_MULTIBOOT_H__
#define __K_MULTIBOOT_H__

#include "klib/kdef.h"

struct MultibootAoutSymbolTable
{
  size_t tabsize;
  size_t strsize;
  size_t addr;
  size_t reserved;
};

struct MultibootElfSectionHeaderTable
{
  size_t num;
  size_t size;
  size_t addr;
  size_t shndx;
};

struct MultibootInfo
{
  size_t flags;
  size_t mem_lo;
  size_t mem_hi;
  size_t boot_device;

  size_t cmd_line;
  size_t mods_count;
  size_t mods_addr;

  union
  {
    struct MultibootAoutSymbolTable aout_sym;
    struct MultibootElfSectionHeaderTable elf_sec;
  } u;

  size_t mmap_len;
  size_t mmap_addr;

  size_t drives_len;
  size_t drives_addr;

  size_t config_table;
  size_t boot_loader_name;

  size_t apm_table;

  size_t vbe_control_info;
  size_t vbe_mode_info;
  uint16_t vbe_mode;
  uint16_t vbe_interface_seg;
  uint16_t vbe_interface_off;
  uint16_t vbe_interface_len;
};

#endif // __K_MULTIBOOT_H__
