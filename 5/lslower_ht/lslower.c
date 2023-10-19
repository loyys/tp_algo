#include "lslower.h"

typedef struct clslower clslower;

struct clslower {
  slower value;
  clslower *next;
};

struct lslower {
  clslower *head;
  clslower *tail;
};

lslower *lslower_empty(void) {
  lslower *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->head = NULL;
  p->tail = NULL;
  return p;
}

bool lslower_is_empty(const lslower *s) {
  return s->head == NULL;
}

size_t lslower_length(const lslower *s) {
  if(lslower_is_empty(s)) {
    return 0;
  }
  size_t len = 1;
  for(clslower *p = s->head->next; p != NULL; p = p->next) {
    len += 1;
  }
  return len;
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
    int c = (p == NULL) ? '\n' : ' ';
    if (fputc(c, stream) == EOF) {
      return EOF;
    }
  }
  return 0;
}

//  lslower_insert_head, lslower_insert_tail : tente d'allouer une cellule
//    contenant une copie de *ptr. Renvoie une valeur non nulle en cas de
//    dépassement de capacité. Insère sinon la cellule allouée en tête (head),
//    en queue (tail) de la liste et renvoie zéro.

int lslower_insert_head(lslower *s, const slower *ptr) {
  clslower *p = malloc(sizeof *p);
  if (p == NULL) {
    return -1;
  }
  p->value = *ptr;
  p->next = s->head;
  if (s->head == NULL) {
    s->tail = p;
  }
  s->head = p;
  return 0;
}

int lslower_insert_tail(lslower *s, const slower *ptr) {
  clslower *p = malloc(sizeof *p);
  if (p == NULL) {
    return -1;
  }
  p->value = *ptr;
  p->next = NULL;
  (s->tail != NULL) ? (s->tail->next = p) : (s->head = p);
  s->tail = p;
  return 0;
}

int lslower_head_value(const lslower *s, slower *ptr) {
  if (lslower_is_empty(s)) {
    return -1;
  }
  *ptr = s->head->value;
  return 0;
}

int lslower_tail_value(const lslower *s, slower *ptr) {
  if (lslower_is_empty(s)) {
    return -1;
  }
  *ptr = s->tail->value;
  return 0;
}


//  lslower_move_head_head, lslower_move_head_tail : renvoie une valeur non
//    nulle si la liste associée à src est vide. Déplace sinon la cellule de
//    tête de la liste associée à src en tête (head_head), en queue (head_tail)
//    de la liste associée à dest et renvoie zéro.
int lslower_move_head_head(lslower *src, lslower *dest) {
  if (lslower_is_empty(src)) {
    return -1;
  }
  clslower *p = src->head;
  src->head = src->head->next;
  p->next = dest->head;
  dest->head = p;
  if (p->next == NULL) {
    dest->tail = p;
  }
  if (src->head == NULL) {
    src->tail = NULL;
  }
  return 0;
}

int lslower_move_head_tail(lslower *src, lslower *dest) {
  if (lslower_is_empty(src)) {
    return -1;
  }
  clslower *p = src->head;
  src->head = (p->next == NULL) ? (src->tail = NULL) : (p->next);
  p->next = NULL;
  (dest->tail == NULL) ? (dest->head = p) : (dest->tail->next = p);
  dest->tail = p;
  return 0;
}

int lslower_move_all_head(lslower *src, lslower *dest) {
  if (src == dest) {
    return 1;
  }
  if (lslower_is_empty(src)) {
    return 0;
  }
  lslower_is_empty(dest)
      ? (dest->tail = src->tail)
      : (src->tail->next = dest->head);
  dest->head = src->head;
  src->tail = NULL;
  src->head = NULL;
  return 0;
}

int lslower_move_all_tail(lslower *src, lslower *dest) {
  if (src == dest) {
    return 1;
  }
  if (lslower_is_empty(src)) {
    return 0;
  }
  lslower_is_empty(dest)
      ? (dest->head = src->head)
      : (dest->tail->next = src->head);
  dest->tail = src->tail;
  src->head = NULL;
  src->tail = NULL;
  return 0;
}
























