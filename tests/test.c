#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif /* _MSC_VER */

#include <greatest.h>

#include "test_lib.h"
#include "test_string.h"

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(lib_suite);
  RUN_SUITE(string_suite);
  GREATEST_MAIN_END();
}
