#ifndef __K_KERNEL_SHELL_CMDS_H__
#define __K_KERNEL_SHELL_CMDS_H__

struct KernelShellCMD
{
  void (*func) (const char *args);
  char *cmd;
};

void ksh_help (const char *);
void ksh_info (const char *);
void ksh_clear (const char *);
void ksh_echo (const char *);
void ksh_loadkeys (const char *);
void ksh_listkeys (const char *);

#endif // __K_KERNEL_SHELL_CMDS_H__
