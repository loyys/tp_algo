#include <stdio.h>
#include <stdlib.h>
#include "str_rec.h"

#define TEST_PTR(fun, text, arg)                                               \
  {                                                                            \
    printf("--- " #fun "\n");                                                  \
    printf("%s\n", text);                                                      \
    char *p = fun(text, arg);                                                  \
    if (p == NULL) {                                                           \
      printf("*");                                                             \
    } else {                                                                   \
      printf("%*c", (int) (p - text + 1), '^');                                \
    }                                                                          \
    printf("%s\n", #arg);                                                      \
  }

#define TEST_SIZE(fun, text, arg)                                              \
  {                                                                            \
    printf("--- " #fun "\n");                                                  \
    printf("%s\n", text);                                                      \
    for (size_t n = fun(text, arg); n > 0; --n) {                              \
      printf(".");                                                             \
    }                                                                          \
    printf("%s\n", #arg);                                                      \
  }

#define TEXT "https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2478.pdf"

int main(void) {
  printf("--- Trials on strings utilities\n"
      "--- Utilities prefixed by 'str_' are homemade\n\n");
  const char *s = TEXT;
  TEST_PTR(str_chr, s, 'd');
  TEST_PTR(str_chr, s, 'a');
  TEST_PTR(str_chr, s, '\0');
  TEST_PTR(str_pbrk, s, "-.:/");
  TEST_PTR(str_pbrk, s, "0123456789");
  TEST_PTR(str_pbrk, s, "abiklmquvxyz");
  TEST_PTR(str_pbrk, s, "f");
  TEST_PTR(str_pbrk, s, "");
  TEST_SIZE(str_spn, s, "abcdefghijklmnopqrstuvwxyz");
  TEST_SIZE(str_spn, s, "-.:/");
  TEST_SIZE(str_spn, s, "-.:/12478cdefghjnoprstw");
  TEST_SIZE(str_spn, s, "");
  return EXIT_SUCCESS;
}
