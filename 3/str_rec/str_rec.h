//  str_rec : String utilities in a recursive approach. Module réimplantant des
//    des fonctions standard sur les chaines de caractères de manière récursive.

#ifndef STR_REC__H
#define STR_REC__H

#include <stddef.h>

//  str_chr, str_pbrk, str_rchr, str_spn : mêmes spécifications que les
//    fonctions strchr, strpbrk, strrchr, strspn, déclarées dans l'en-tête
//    standard <string.h>.

extern char *str_chr(const char *s, int c);
extern char *str_pbrk(const char *s1, const char *s2);
extern char *str_rchr(const char *s, int c);
extern size_t str_spn(const char *s1, const char *s2);

#endif
