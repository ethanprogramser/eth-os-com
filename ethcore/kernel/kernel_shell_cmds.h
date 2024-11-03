#ifndef __K_KERNEL_SHELL_CMDS_H__
#define __K_KERNEL_SHELL_CMDS_H__

struct KernelShellCMD
{
  void (*cmd) (char *);
  char *str;
};

void ksh_clear (char *);

#endif // __K_KERNEL_SHELL_CMDS_H__
