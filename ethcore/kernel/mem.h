#ifndef __K_MEM_H__
#define __K_MEM_H__

#include "klib/kdef.h"
#include "klib/kint.h"

void memory_init (size_t high, size_t phys_alloc_start);
void memory_map_page (size_t vaddr, size_t paddr, uint32_t flags);

#endif // __K_MEM_H__
