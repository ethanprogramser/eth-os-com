#ifndef __K_KERNEL_SHELL_CMDS_H__
#define __K_KERNEL_SHELL_CMDS_H__

struct KernelShellCMD
{
  void (*func) (char *);
  char *cmd;
};

void ksh_help (char *);
void ksh_info (char *);
void ksh_clear (char *);

#endif // __K_KERNEL_SHELL_CMDS_H__
