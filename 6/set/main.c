//  Affiche :
//  - sur la sortie erreur, le nombre de mots lus sur l'entrée standard puis
//      le nombre de mots lus différents ;
//  - sur la sortie standard, la liste de ces mots,
//      dans l’ordre lexicographique.
//  Limitations :
//  - les mots sont obtenus par lecture sur l'entrée des suites consécutives de
//      longueur maximale de caractères qui ne sont pas de la catégorie
//      isspace ;
//  - toute suite de tels caractères de longueur strictement supérieure à
//      WORD_LENGTH_MAX est découpée en plusieurs mots.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "set.h"

#define STR(x)  #x
#define XSTR(x) STR(x)

#define WORD_LENGTH_MAX 1

//  str_set_free : libere les chaines de caractères référencées dans l'ensemble
//    associé à s.
static void str_set_free(set *s) {
  while (!set_is_empty(s)) {
    char *t = set_remove(s, set_pick(s));
    free(t);
  }
}

int main(void) {
  int main_ret = EXIT_SUCCESS;
  set *s = set_empty((int (*)(const void *, const void *))strcmp);
  if (s == NULL) {
    goto error_capacity;
  }
  long int n = 0;
  char w[WORD_LENGTH_MAX + 1];
  while (scanf("%" XSTR(WORD_LENGTH_MAX) "s", w) == 1) {
    ++n;
    if (strlen(w) == WORD_LENGTH_MAX) {
      int c = fgetc(stdin);
      if (c != EOF && !isspace(c))  {
        ungetc(c, stdin);
        fprintf(stderr,
            "*** Warning: Word '%s...' possibly sliced\n", w);
      }
    }
    char *t = malloc(strlen(w) + 1);
    strcpy(t, w);
    char *ref = set_add(s, t);
    if (ref == NULL) {
      goto error_capacity;
    }
    if (ref != t) {
      free(t);
    }
  }
  if (!feof(stdin)) {
    fprintf(stderr, "--- Error: error on stdin");
    goto dispose;
  }
  fprintf(stderr,
      "--- Info: Number of words read: %ld\n", n);
  fprintf(stderr,
      "--- Info: Number of different words read: %zu\n", set_card(s));
  while (!set_is_empty(s)) {
    char *t = set_min(s);
    printf("%s\n", t);
    set_remove(s, t);
    free(t);
  }
  goto dispose;
error_capacity:
  fprintf(stderr, "--- Error: Cannot allocate memory");
  str_set_free(s);
  main_ret = EXIT_FAILURE;
dispose:
  set_dispose(&s);
  return main_ret;
}
