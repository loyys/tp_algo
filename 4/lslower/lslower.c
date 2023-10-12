#include "lslower.h"
#include <stdio.h>

typedef struct clslower clslower;

struct clslower {
  slower value;
  clslower *next;
};

struct lslower {
  clslower *head;
};

lslower *lslower_empty(void) {
  lslower *s = malloc(sizeof *s);
  if (s == NULL) {
    return NULL;
  }
  s->head = NULL;
  return s;
}

bool lslower_is_empty(const lslower *s) {
  return s->head == NULL;
}

void lslower_dispose(lslower **sptr) {
  if (*sptr == NULL) {
    return;
  }
  clslower *t = (*sptr)->head;
  while (t != NULL) {
    clslower *p = t;
    t = t->next;
    free(p);
  }
  free(*sptr);
  *sptr = NULL;
}

int lslower_fput(const lslower *s, FILE *stream) {
  clslower *p = s == NULL ? NULL : s->head;
  while (p != NULL) {
    if (slower_fput(&p->value, stream) == EOF) {
      return EOF;
    }
    p = p->next;
    int c = p == NULL ? 0 : ' ';
    if (c != 0) {
      if (fputc(c, stream) == EOF) {
        return EOF;
      }
    }
  }
  if (fputc('\n', stream) == EOF) {
    return EOF;
  }
  return 0;
}

int lslower_insert_head(lslower *s, const slower *ptr) {
  clslower *p = malloc(sizeof *p);
  if (p == NULL) {
    return -1;
  }
  p->value = *ptr;
  p->next = s->head;
  s->head = p;
  return 0;
}

int lslower_head_value(const lslower *s, slower *ptr) {
  if (lslower_is_empty(s)) {
    return -1;
  }
  *ptr = s->head->value;
  return 0;
}

int lslower_move_head_head(lslower *src, lslower *dest) {
  if (lslower_is_empty(src)) {
    return -1;
  }
  clslower *p = src->head;
  src->head = src->head->next;
  p->next = dest->head;
  dest->head = p;
  return 0;
}
