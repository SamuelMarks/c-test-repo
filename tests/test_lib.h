#include <c_test_repo_configure.h>

#include <greatest.h>
#include <stdbool.h>

#include <library.h>

TEST x_lib_should_be(void) {
  /* TODO: Actually test things */
  char *s = dstr(NULL, "foo");

  dstr(&s, "bar%s%d", "can", 7);
  dstr(&s, "bar%s%s", "can", "baz");

  printf("[[%s]]\n", s);

  free(s);
  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(lib_suite) { RUN_TEST(x_lib_should_be); }
