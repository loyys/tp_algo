#include <stdio.h>
#include <stdlib.h>
#include "balpar.h"
#include <string.h>

#define MAX_LEN (10)

int main() {
  char buff[MAX_LEN];
  fgets(buff, MAX_LEN, stdin);
  for (int i = 0; i < MAX_LEN; ++i) {
    if (buff[i] == '\n') {
      buff[i] = '\0';
    }
  }
  char *p = balpar(buff);
  fprintf(stdout, "%s\n", buff);
  if (p != NULL) {
    printf("%*c\n", (int) (p - buff + 1), '^');
  } else {
    printf("Done\n");
  }
  return EXIT_SUCCESS;
}
