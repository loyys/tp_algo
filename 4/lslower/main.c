#include <stdio.h>
#include <stdlib.h>
#include "lslower.h"
#include "lslower_ext.h"

//  stop : affiche sur la sortie standard une invite de commande. Lit ensuite
//    des caractères sur l'entrée standard jusqu'à détecter la fin de l'entrée
//    ou obtenir 'q', 'Q' ou '\n'. Renvoie zéro si '\n' est obtenu. Provoque
//    sinon la terminaison normale du programme en signifiant à l’environnement
//    d’exécution un succès.
int stop(void);

#define ON_ERROR_GOTO(expr, cause, label)                                      \
  if ((expr) != 0) {                                                           \
    fprintf(stderr, "*** Error line: %d test: %s cause: %s\n",                 \
    __LINE__, #expr, cause);                                                   \
    goto label;                                                                \
  }

#define NMEMB 0

int main(void) {
  fputs(
      "--- Tests on lslower module\n"
      "--- Type ctrl-d or enter 'q' or 'Q' to exit\n\n", stdout);
  srand(0);
  do {
    lslower *s = lslower_empty();
    lslower *s2 = lslower_empty();
    ON_ERROR_GOTO(s == NULL, "Heap_overflow", dispose)
    ON_ERROR_GOTO(s2 == NULL, "Heap_overflow", dispose)
    for (int k = 0; k < NMEMB; ++k) {
      slower x;
      slower_rand(&x);
      ON_ERROR_GOTO(lslower_insert_head(s, &x) != 0, "Heap overflow", dispose);
    }
    ON_ERROR_GOTO(lslower_fput(s, stdout) == EOF, "Internal error", dispose)
    while (lslower_move_head_head(s, s2) == 0) {
      lslower_fput(s, stdout);
      lslower_fput(s2, stdout);
    }
dispose:
    lslower_dispose(&s);
    lslower_dispose(&s2);
  } while (!stop());
}

#define PROMPT "> "

int stop(void) {
  fputs(PROMPT, stdout);
  while (1) {
    int c = getchar();
    if (c == EOF || c == 'q' || c == 'Q') {
      fputc('\n', stdout);
      exit(EXIT_SUCCESS);
    }
    if (c == '\n') {
      return 0;
    }
  }
}
