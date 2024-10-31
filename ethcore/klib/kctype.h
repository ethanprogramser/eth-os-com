#ifndef __K_KLIB_CTYPE_H__
#define __K_KLIB_CTYPE_H__

int __kisalnum (char c);
int __kisalpha (char c);
int __kisblank (char c);
int __kiscntrl (char c);
int __kisdigit (char c);
int __kisgraph (char c);
int __kislower (char c);
int __kisprint (char c);
int __kispunct (char c);
int __kisspace (char c);
int __kisupper (char c);
int __kisxdigit (char c);

char __ktoupper (char c);
char __ktolower (char c);

#endif // __K_KLIB_CTYPE_H__
