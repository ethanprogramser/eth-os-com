#ifndef __K_KEYBOARD_H__
#define __K_KEYBOARD_H__

struct InterruptRegisters;

void initKeyboard ();
void keyboardHandler (struct InterruptRegisters *regs);
void append (char *part);

#endif // __K_KEYBOARD_H__
