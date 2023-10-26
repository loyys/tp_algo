#include "lslower_ext.h"

void lslower_partition_pivot_tail(lslower *s,
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
      lslower_move_head_tail(s, slth);
    } else if (c > 0) {
      lslower_move_head_tail(s, sgth);
    } else {
      lslower_move_head_tail(s, seq);
    }
  }
}

int lslower_quicksort_stable(lslower *s) {
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
  lslower_partition_pivot_tail(s, slth, seq, sgth);
  lslower_quicksort_stable(slth);
  lslower_quicksort_stable(sgth);
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
