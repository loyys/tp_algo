#include "str_rec.h"
#include <stdbool.h>
#include <limits.h>

static bool is_char(int c) {
  return (c <= CHAR_MAX) && (c >= CHAR_MIN);
}

static char *str_chr_rec(const char *s, int c) {
  if (*s == '\0') {
    return c == *s ? (char *) s : NULL;
  }
  if (*s == c) {
    return (char *) s;
  }
  return str_chr_rec(s + 1, c);
}

char *str_chr(const char *s, int c) {
  if (!is_char(c)) {
    return NULL;
  }
  return str_chr_rec(s, c);
}

char *str_pbrk(const char *s1, const char *s2) {
  if (*s1 == '\0') {
    return NULL;
  }
  const char *s;
  if ((s = str_chr(s2, *s1)) != NULL) {
    return (char *) s1;
  }
  return str_pbrk(s1 + 1, s2);
}

static char *str_rchr_rec(const char *fst, const char *lst, int c) {
  if (lst == fst) {
    return *lst == c ? (char *) lst : NULL;
  }
  if (*lst == c) {
    return (char *) lst;
  }
  return str_rchr_rec(fst, lst - 1, c);
}

static const char *str_get_nul(const char *s) {
  if (*s == '\0') {
    return s;
  }
  return str_get_nul(s + 1);
}

char *str_rchr(const char *s, int c) {
  if (!is_char(c)) {
    return NULL;
  }
  return str_rchr_rec(s, str_get_nul(s), c);
}

static size_t str_spn_rec(size_t len, const char *s1, const char *s2) {
  if (*s1 == '\0') {
    return len;
  }
  if (str_chr(s2, *s1) == NULL) {
    return len;
  }
  return str_spn_rec(len + 1, s1 + 1, s2);
}

size_t str_spn(const char *s1, const char *s2) {
  const char *s = (const char *) str_pbrk(s1, s2);
  if (s == NULL) {
    return 0;
  }
  return str_spn_rec(1, s + 1, s2);
}
