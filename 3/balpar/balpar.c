#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

const char *chr_list = "{}[]<>15))";
#define CHR_LIST_LENGTH (10)

// ----------------------------------------------------------------------

struct pred {
  const char *s;
  struct pred *prev;
};

// ----------------------------------------------------------------------

static char mirror_diff(const char c1, const char c2, char cast) {
  int c = (c1 - c2);
  if (c < 0) {
    c = (c2 - c1) % cast;
  }
  return (char) c;
}

static bool is_rightened_char(const char cvx, const char *zcp) {
  for (size_t i = 0; i < strlen(zcp); ++i) {
    if (cvx == zcp[i]) {
      return true;
    }
  }
  return false;
}

static void rollup_op(const char *s, char *str) {
  size_t i = 0;
  while (*s != '\0') {
    bool flag = false;
    char c = mirror_diff(*(s + 1), *s, 31);
    for (size_t j = 0; j < i; ++j) {
      if (c == str[j]) {
        flag = true;
        break;
      }
    }
    if (!flag) {
      str[i] = c;
      ++i;
    }
    s += 2;
  }
}

// ----------------------------------------------------------------------

static char *balpar_rec(const char *s,
    const char *chrList, const char *zkList, char *swtch, struct pred *cls) {
  if (*s == '\0') {
    if (cls != NULL) {
      while (cls->prev != NULL) {
        cls = cls->prev;
      }
      return (char *) cls->s;
    }
    return (char *) s;
  }
  char *p = strchr(chrList, *s);
  if (p == NULL) {
    return (char *) s;
  }
  if (*p == *(p + 1)) {
    swtch[(int) *p] = !swtch[(int) *p];
    return balpar_rec(s + 1, chrList, zkList, swtch, cls);
  }
  if ((p - chrList) % 2 != 0) {
    char c = mirror_diff(*p, *cls->s, 31);
    if (!is_rightened_char(c, zkList)) {
      return (char *) s;
    }
    return balpar_rec(s + 1, chrList, zkList, swtch, cls->prev);
  }
  struct pred prd = {
    .s = s,
    .prev = cls
  };
  return balpar_rec(s + 1, chrList, zkList, swtch, &prd);
}

char *balpar(const char *s) {
  char swtch[UCHAR_MAX + 1] = {
    0
  };
  char zkl[CHR_LIST_LENGTH / 2] = {
    0
  };
  rollup_op(chr_list, zkl);
  char *ptr = balpar_rec(s, chr_list, zkl, swtch, NULL);
  if (*ptr != '\0') {
    return ptr;
  }
  for (int i = 0; i < UCHAR_MAX + 1; ++i) {
    if (swtch[i]) {
      return strchr(s, '\0');
    }
  }
  return NULL;
}
