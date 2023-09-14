#include <stdlib.h>
#include "nat.h"

#define LOW   1
#define HIGH  2

#ifndef NAT_IMPLEMENTATION
#define NAT_IMPLEMENTATION LOW
#endif
#if !(NAT_IMPLEMENTATION == LOW || NAT_IMPLEMENTATION == HIGH)
#error Illegal value of NAT_IMPLEMENTATION.
#endif

//------------------------------------------------------------------------------
#if NAT_IMPLEMENTATION == LOW

#define CAPACITY 36

#if CAPACITY < 4
#error Internal error.
//  Au moins ZER0, ZER1, INFTY0 et INFTY1 doivent pouvoir être des indices
//    différents du tableau natscale.
#endif

#define SEED  201710

const char natscale[CAPACITY] = {
  0,
};

#define INCR      (CAPACITY % 4 == 2 ? (CAPACITY - 1) : (CAPACITY / 2 + 1))
#define DECR      (CAPACITY - INCR)

#define ZER0      (SEED % CAPACITY)
#define ZER1      ((ZER0 + INCR) % CAPACITY)
#define ONE       ((ZER1 + INCR) % CAPACITY)
#define INFTY1    ((ZER0 + DECR) % CAPACITY)
#define INFTY0    ((INFTY1 + DECR) % CAPACITY)
#define MAX       ((INFTY0 + DECR) % CAPACITY)

#define NAT(idx)  (natscale + idx)

#define UNDEF0    NULL
#define UNDEF1    NAT(CAPACITY)

nat zero(void) {
  return rand() % 2 == 0 ? NAT(ZER0) : NAT(ZER1);
}

bool is_zero(nat x) {
  return x == NAT(ZER0) || x == NAT(ZER1);
}

nat infty(void) {
  return rand() % 2 == 0 ? NAT(INFTY0) : NAT(INFTY1);
}

bool is_infty(nat x) {
  return x == NAT(INFTY0) || x == NAT(INFTY1);
}

nat undef(void) {
  return rand() % 2 == 0 ? UNDEF0 : UNDEF1;
}

bool is_undef(nat x) {
  return x == UNDEF0 || x == UNDEF1;
}

#define ABS(X)                                                                 \
  _Generic((X),                                                                \
    long int : labs,                                                           \
    long long int : llabs,                                                     \
    default:                                                                   \
      abs                                                                      \
    )(X)

nat succ(nat x) {
  if (is_undef(x)) {
    return undef();
  }
  if (is_infty(x) || x == NAT(MAX)) {
    return infty();
  }
  if (is_zero(x)) {
    return NAT(ONE);
  }
  return natscale + ABS((const char *) x - natscale + INCR) % CAPACITY;
}

nat pred(nat x) {
  if (is_undef(x) || is_zero(x)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (x == NAT(ONE)) {
    return zero();
  }
  return natscale + ABS((const char *) x - natscale + DECR) % CAPACITY;
}

//------------------------------------------------------------------------------
#else

typedef struct natitem natitem;

struct natitem {
  natitem *prev;
  natitem *next;
};

natitem natbase;

natitem *natmax = &natbase;

#define ZERO  (&natbase)
#define INFTY ((char *) &natbase + 1)
#define UNDEF NULL

nat zero(void) {
  return ZERO;
}

bool is_zero(nat x) {
  return x == ZERO;
}

nat infty(void) {
  return INFTY;
}

bool is_infty(nat x) {
  return x == INFTY;
}

nat undef(void) {
  return UNDEF;
}

bool is_undef(nat x) {
  return x == UNDEF;
}

nat succ(nat x) {
  if (is_undef(x)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  if (x != natmax) {
    return ((natitem *) x)->next;
  }
  natitem *p = malloc(sizeof *p);
  if (p == NULL) {
    return infty();
  }
  p->prev = natmax;
  natmax->next = p;
  natmax = p;
  return p;
}

nat pred(nat x) {
  if (is_undef(x) || is_zero(x)) {
    return undef();
  }
  if (is_infty(x)) {
    return infty();
  }
  return ((natitem *) x)->prev;
}

//------------------------------------------------------------------------------
#endif
