#include "kernel/kernel_shell_cmds.h"
#include "kernel/info.h"
#include "kernel/vga.h"
#include "klib/kio.h"

static const char *ksh_help_output
    = { "List of all available commands\n"
        "- help: Display this message\n"
        "- info: Display information about the OS\n"
        "- clear: Clear screen\n"
        "\n" };

void
ksh_help (char *_)
{
  __kputs (ksh_help_output);
}

void
ksh_info (char *_)
{
  // OS name
  __kputs ("=== OS INFORMATION ===:\n");
  char ver_major = __K_VERSION_MAJOR + '0';
  char ver_minor = __K_VERSION_MINOR + '0';
  char ver_patch = __K_VERSION_PATCH + '0';
  char version[0xFF] = { ver_major, '.', ver_minor, '.', ver_patch, 0 };
  __kputs ("OS name: ");
  __kputs (__K_NAME "\n");
  __kputs ("Version: ");
  __kputs (version);
  __kputc ('\n');
  __kputs ("Architecture: " __K_ARCHITECTURE);
  __kputs ("\n\n");

  // Maintainers
  __kputs ("=== MAINTAINERS ===\n");
  size_t maintainers_list_len;
  const char **maintainers_list
      = __kinfo_get_maintainers (&maintainers_list_len);
  for (size_t i = 0; i < maintainers_list_len; ++i)
  {
    __kputs (maintainers_list[i]);
    __kputc ('\n');
  }
  __kputc ('\n');

  // Contributors
  __kputs ("=== CONTRIBUTORS ===\n");
  size_t contributors_list_len;
  const char **contributors_list
      = __kinfo_get_contributors (&contributors_list_len);
  for (size_t i = 0; i < contributors_list_len; ++i)
  {
    __kputs (contributors_list[i]);
    __kputc ('\n');
  }
  __kputc ('\n');
}

void
ksh_clear (char *_)
{
  vga_clear_screen ();
}
