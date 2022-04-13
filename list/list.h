#ifndef C_TEST_REPO_LIST_H
#define C_TEST_REPO_LIST_H

#include <stdlib.h>

#if defined(_WIN32) || defined(__WIN32__) || defined(__WINDOWS__)
#include <BaseTsd.h>
#include <errno.h>
typedef SSIZE_T ssize_t;
#else
#include <sys/errno.h>
#endif

#include "c_test_repo_export.h"

struct elem {
  long data;
  struct elem *next;
};

extern C_TEST_REPO_LIST_EXPORT struct elem *append(struct elem *, long);

extern C_TEST_REPO_LIST_EXPORT struct elem *addToList(struct elem *, long);

extern C_TEST_REPO_LIST_EXPORT struct elem *deleteFromList(struct elem *, size_t);

extern C_TEST_REPO_LIST_EXPORT void printList(struct elem *);

#endif /* C_TEST_REPO_LIST_H */
