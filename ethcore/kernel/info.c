#include "kernel/info.h"

static const char *__kmaintainers[] = {
  "ethanprogramser",
  "Nyvyme",
};
static const char *__kcontributors[] = {
  "ethanprogramser",
  "Nyvyme",
  "grenadieren",
  "asdasda3456",
  "jamescraft10",
};

const char **
__kinfo_get_maintainers (size_t *len)
{
  *len = sizeof (__kmaintainers) / sizeof (__kmaintainers[0]);
  return __kmaintainers;
}

const char **
__kinfo_get_contributors (size_t *len)
{
  *len = sizeof (__kcontributors) / sizeof (__kcontributors[0]);
  return __kcontributors;
}
