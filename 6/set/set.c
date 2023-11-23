//  set.c : partie implantation d'un module polymorphe pour la spécification ENS
//    du TDA Ens(T) ainsi que pour son extension optionnelle ENSMIN.

#include "set.h"

typedef struct cset cset;
struct cset{
  void *ref;
  cset *next;
};

struct set {
  int (*compar)(const void *, const void *);
  size_t card;
  cset *head;
};

set *set_empty(int (*compar)(const void *, const void *)) {
  set *p = malloc(sizeof *p);
  if (p == NULL) {
    return NULL;
  }
  p->compar = compar;
  p->card = 0;
  p->head = NULL;
  return p;
}

void set_dispose(set **sptr) {
  if (*sptr == NULL) {
    return;
  }
  cset *p = (*sptr)->head;
  while (p != NULL) {
    cset *t = p;
    p = p->next;
    free(t);
  }
  free(*sptr);
  *sptr = NULL;
}

static cset **cset__search(cset * const *p, const void *ref,
    int (*compar)(const void *, const void *)) {
  while (*p != NULL) {
    if (compar((*p)->ref, ref) == 0) {
      return (cset **)p;
    }
    p = &(*p)->next;
  }
  return NULL;
}

void *set_add(set *s, const void *ref) {
  if (ref == NULL) {
    return NULL;
  }
  {
    cset **r = cset__search(&s->head, ref, s->compar);
    if (r != NULL) {
      return (void *)(*r)->ref;
    }
  }
  {
    cset *r = malloc(sizeof *r);
    if (r == NULL) {
      return NULL;
    }
    r->ref = (void *)ref;
    r->next = s->head;
    s->head = r;
    ++s->card;
  }
  return (void *)ref;
}

void *set_remove(set *s, const void *ref) {
  if (ref == NULL) {
    return NULL;
  }
  cset **r = cset__search(&s->head, ref, s->compar);
  if (r == NULL) {
    return NULL;
  }
  cset *p = *r;
  *r = (*r)->next;
  p->next = NULL;
  char *t = p->ref;
  free(p);
  return (void *)t;
}

void *set_pick(set *s) {
  return s->head->ref;
}

bool set_is_empty(set *s) {
  return s->head == NULL;
}

void *set_search(set *s, const void *ref) {
  if (ref == NULL) {
    return NULL;
  }
  cset **p = cset__search(&s->head, ref, s->compar);
  return p == NULL ? NULL : (void *)(*p)->ref;
}

size_t set_card(set *s) {
  return s->card;
}

#if defined SET_WANT_EXT && SET_WANT_EXT != 0

//  set_min : renvoie NULL si l'ensemble associé à s est vide. Recherche sinon
//    dans l'ensemble la référence d'un objet minimal au sens de la fonction de
//    comparaison. Renvoie la référence trouvée.
void *set_min(set *s) {
  if (set_is_empty(s)) {
    return NULL;
  }
  void *min = s->head->ref;
  cset *p = s->head->next;
  while (p != NULL) {
    if (s->compar(p->ref, min) < 0) {
      min = p->ref;
    }
    p = p->next;
  }
  return min;
}
#endif
