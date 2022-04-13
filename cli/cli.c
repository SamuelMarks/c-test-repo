#include "cli.h"
#include "list.h"

int main(int argC, char *argV[]) {
  struct elem * node = NULL;
  int i;

  if (argC == 1)
    printf("Usage : %s <list of integers to be inserted into the list>",
           argV[0]);
  else {
    for (i = 2; i <= argC; i++)
      node = append(node, atoi(argV[i - 1]));

    printList(node);

    do {
      printf("\nEnter position of element to be removed (1-%d) : ", argC - 1);

      scanf("%d", &i);

      if (i > 0 && i <= argC - 1) {
        node = deleteFromList(node, i);
        printList(node);
      }
    } while (i > argC - 1 || i <= 0);
  }
  return 0;
}
