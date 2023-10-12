#include "lslower_ext.h"
#include "lslower.h"
#include "slower.h"

#undef SLOWER_COMPAR_LENGTH
#define SLOWER_COMPAR_LENGTH (SLOWER_LENGTH / 2)

//  lslower_move_all_head : renvoie une valeur non nulle si src et dest
//    désignent le même objet (autrement dit si « src == dest ») ou en cas de
//    dépassement de capacité. Déplace sinon en tête de la liste associée à dest
//    la suite des cellules de la liste associée à src et renvoie zéro (à la
//    terminaison, la liste associée à src est vide et la liste associée à dest
//    est la concaténation des listes originelles associées à src et dest).

int lslower_move_all_head(lslower *src, lslower *dest) {
  if (src == dest) {
    return 1;
  }
  lslower *tmp = lslower_empty();
  if (tmp == NULL) {
    return -1;
  }
  while (!lslower_is_empty(src) && lslower_move_head_head(src, tmp) == 0) {
  }
  while (!lslower_is_empty(tmp) && lslower_move_head_head(tmp, dest) == 0) {
  }
  lslower_dispose(&tmp);
  return 0;
}

//  lslower_partition_pivot : sans effet si la liste associée à s est vide.
//    Déplace sinon respectivement dans les listes associées à slth, seq et
//    sgth, les cellules de la liste associée à s dont les valeurs du type
//    « slower » sont strictement inférieures, égales et strictement supérieures
//    à la valeur de type « slower » de la cellule originellement en tête de la
//    liste associée à s (à la terminaison, la liste associée à s est vide).
void lslower_partition_pivot(lslower *s,
    lslower *slth, lslower *seq, lslower *sgth) {
  if (lslower_is_empty(s)) {
    return;
  }
  lslower_move_head_head(s, seq);
  while (!lslower_is_empty(s)) {
    slower p1, p2;
    lslower_head_value(s, &p1);
    lslower_head_value(seq, &p2);
    int c = slower_compar(&p1, &p2);
    if (c < 0) {
      lslower_move_head_head(s, slth);
    } else if (c > 0) {
      lslower_move_head_head(s, sgth);
    } else {
      lslower_move_head_head(s, seq);
    }
  }
}

//  lslower_quicksort : tente de recomposer la liste associée à s selon la
//    méthode du tri rapide. Renvoie zéro en cas de succès, une valeur non nulle
//    en cas d'échec.

int lslower_quicksort(lslower *s) {
  if (lslower_is_empty(s)) {
    return 0;
  }
  lslower *slth = lslower_empty();
  lslower *seq = lslower_empty();
  lslower *sgth = lslower_empty();
  if (slth == NULL || seq == NULL || sgth == NULL) {
    lslower_dispose(&slth);
    lslower_dispose(&seq);
    lslower_dispose(&sgth);
    return -1;
  }
  lslower_partition_pivot(s, slth, seq, sgth);
  lslower_quicksort(slth);
  lslower_quicksort(sgth);
  if (!lslower_is_empty(sgth)) {
    lslower_move_all_head(sgth, s);
  }
  if (!lslower_is_empty(seq)) {
    lslower_move_all_head(seq, s);
  }
  if (!lslower_is_empty(slth)) {
    lslower_move_all_head(slth, s);
  }
  lslower_dispose(&slth);
  lslower_dispose(&seq);
  lslower_dispose(&sgth);
  return 0;
}
