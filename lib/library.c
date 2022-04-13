#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

/* for `vsprintf_s` */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif /* _MSC_VER */

char *dstr(char **unto, const char *fmt, ...) {
  va_list args;
  size_t base_length = unto && *unto ? strlen(*unto) : 0;
  int length;
  char *result;

  va_start(args, fmt);
  /* check length for failure */
  length = vsnprintf(NULL, 0, fmt, args);
  va_end(args);

  /* check result for failure */
  result = realloc(unto ? *unto : NULL, base_length + length + 1);

  va_start(args, fmt);
  /* check for failure*/
  vsprintf(result + base_length, fmt, args);
  va_end(args);

  if (unto)
    *unto = result;

  return result;
}

void hello(void) { printf("Hello, World!\n"); }
