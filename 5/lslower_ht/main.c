#include <stdio.h>
#include <stdlib.h>
#include "lslower.h"

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

#define NMEMB 4

int main(void) {
  fputs(
      "--- Tests on lslower modules\n"
      "--- Type ctrl-d or enter 'q' or 'Q' to exit\n\n", stdout);
  srand(0);
  do {
    lslower *s = lslower_empty();
    lslower *s2 = lslower_empty();
    lslower *ss = lslower_empty();
    lslower *s4 = lslower_empty();
    ON_ERROR_GOTO(s == NULL, "Heap_overflow", dispose)
    ON_ERROR_GOTO(s2 == NULL, "Heap_overflow", dispose)
    for (int k = 0; k < NMEMB; ++k) {
      slower x;
      slower_rand(&x);
      ON_ERROR_GOTO(lslower_insert_head(s, &x) != 0, "Heap overflow", dispose);
      ON_ERROR_GOTO(lslower_insert_tail(ss, &x) != 0, "Heap overflow", dispose);
    }
    fputs("--- s ss ---\n", stdout);
    ON_ERROR_GOTO(lslower_fput(s, stdout) == EOF, "Internal error", dispose)
    ON_ERROR_GOTO(lslower_fput(ss, stdout) == EOF, "Internal error", dispose)
    fputs("--- Head Head, Head Tail ---\n", stdout);
    int i = 2;// NMEMB / 3;
    while (i != 0
        && lslower_move_head_head(s, s2) == 0
        && lslower_move_head_tail(ss, s4) == 0) {
      lslower_fput(s, stdout);
      lslower_fput(s2, stdout);
      fputs("---\n", stdout);
      lslower_fput(ss, stdout);
      lslower_fput(s4, stdout);
      --i;
    }
    fputs("--- ALL HEAD ---\n", stdout);
    ON_ERROR_GOTO(lslower_move_all_head(s, s2) != 0, "Internal error", dispose)
    lslower_fput(s, stdout);
    lslower_fput(s2, stdout);
    fputs("--- ALL TAIL---\n", stdout);
    ON_ERROR_GOTO(lslower_move_all_tail(ss, s4) != 0, "Internal error", dispose)
    lslower_fput(ss, stdout);
    lslower_fput(s4, stdout);
    fputs("--- Length ---\n", stdout);
    fprintf(stdout, "s : %zu\nss : %zu\ns2 : %zu\ns4 : %zu\n",
        lslower_length(s), lslower_length(ss),
        lslower_length(s2), lslower_length(s4));
dispose:
    lslower_dispose(&s);
    lslower_dispose(&s2);
    lslower_dispose(&ss);
    lslower_dispose(&s4);
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
