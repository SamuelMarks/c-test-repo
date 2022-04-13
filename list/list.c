#include <stdio.h>

#include "list.h"

struct elem *append(struct elem *root, long num) {
  struct elem **insert = &root;
  while (*insert)
    insert = &insert[0]->next;
  *insert = malloc(sizeof **insert);
  if (!*insert)
    exit(ENOMEM);
  insert[0]->next = NULL;
  insert[0]->data = num;
  return root;
}

struct elem *deleteFromList(struct elem *node, size_t pos) {
  size_t i = 1;
  struct elem *temp, *iter;

  if (node != NULL) {
    iter = node;

    if (pos == 1) {
      node = node->next;
      iter->next = NULL;
      free(iter);
    }

    else {
      while (i++ != pos - 1)
        iter = iter->next;
      temp = iter->next;
      iter->next = temp->next;
      temp->next = NULL;
      free(temp);
    }
  }
  return node;
}

void printList(struct elem *node) {
  struct elem *iter;
  puts("List contains following elements : \n");

  for (iter = node; iter != NULL; iter = iter->next)
    printf("%ld ", iter->data);
}
