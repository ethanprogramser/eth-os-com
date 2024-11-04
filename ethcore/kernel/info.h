#ifndef __K_INFO_H__
#define __K_INFO_H__

#include "klib/kdef.h"

#define __K_NAME "Eth-OS Community Edition"
#define __K_VERSION_MAJOR 0
#define __K_VERSION_MINOR 1
#define __K_VERSION_PATCH 0
#define __K_ARCHITECTURE "x86-32"

const char **__kinfo_get_maintainers (size_t *len);
const char **__kinfo_get_contributors (size_t *len);

#endif // __K_INFO_H__
