#ifndef BALPAR__H
#define BALPAR__H

//  balpar : renvoie NULL si la chaine de caractères pointée par s est une
//    expression bien parenthésée (ouvrant "(" et fermant ")"). Renvoie sinon
//    l'adresse du premier caractère de la chaine s inattendu ou non apparié.
extern char *balpar(const char *s);

#endif
