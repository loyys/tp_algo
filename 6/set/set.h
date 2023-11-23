//  set.h : partie interface d'un module polymorphe pour la spécification ENS du
//    du TDA Ens(T) ainsi que pour son extension optionnelle ENSMIN.

//  LA SEULE MODIFICATION AUTORISÉE DE CE SOURCE CONCERNE LA LIGNE 106.
//  TOUTE ÉVENTUELLE MODIFICATION DE LA LIGNE 106 DOIT SE CONFORMER AUX
//    SPÉCIFICATIONS EXPRIMÉES AUX LIGNES 87-100.

#ifndef SET__H
#define SET__H

//  Fonctionnement général :
//  - la structure de données ne stocke pas d'objets mais des références vers
//      ces objets. Les références sont du type générique « void * » ;
//  - si des opérations d'allocation dynamique sont effectuées, elles le sont
//      pour la gestion propre de la structure de données, et en aucun cas pour
//      réaliser des copies ou des destructions d'objets ;
//  - les fonctions qui possèdent un paramètre de type « set * » ou « set ** »
//      ont un comportement indéterminé lorsque ce paramètre ou sa déréférence
//      n'est pas l'adresse d'un contrôleur préalablement renvoyée avec succès
//      par la fonction set_empty et non révoquée depuis par la fonction
//      set_dispose ;
//  - aucune fonction ne peut ajouter NULL à la structure de données ;
//  - les fonctions de type de retour « void * » renvoient NULL en cas d'échec.
//      En cas de succès, elles renvoient une référence actuellement ou
//      auparavant stockée par la structure de données ;
//  - l'implantation des fonctions dont la spécification ne précise pas qu'elles
//      doivent gérer les cas de dépassement de capacité ne doivent avoir
//      affaire avec aucun problème de la sorte.

#include <stdbool.h>
#include <stdlib.h>

//- STANDARD -------------------------------------------------------------------

//  struct set, set : type et nom de type d'un contrôleur regroupant les
//    informations nécessaires pour gérer un ensemble de références d'objets
//    quelconques.
typedef struct set set;

//  set_empty : tente d'allouer les ressources nécessaires pour gérer un nouvel
//    ensemble initialement vide. La fonction de comparaison des objets via
//    leurs références est pointée par compar. Renvoie NULL en cas de
//    dépassement de capacité. Renvoie sinon un pointeur vers le contrôleur
//    associé à l'ensemble.
extern set *set_empty(int (*compar)(const void *, const void *));

//  set_dispose : sans effet si *sptr vaut NULL. Libère sinon les ressources
//    allouées à la gestion de l'ensemble associé à *sptr puis affecte NULL à
//    *sptr.
extern void set_dispose(set **sptr);

//  set_add : renvoie NULL si ref vaut NULL. Recherche sinon dans l'ensemble
//    associé à s la référence d'un objet égal à celui de référence ref au sens
//    de la fonction de comparaison. Si la recherche est positive, renvoie la
//    référence trouvée. Tente sinon d'ajouter ref à l'ensemble ; renvoie NULL
//    en cas de dépassement de capacité ; renvoie sinon ref.
extern void *set_add(set *s, const void *ref);

//  set_remove : recherche dans l'ensemble associé à s la référence d'un objet
//    égal à celui de référence ref au sens de la fonction de comparaison. Si la
//    recherche est négative, renvoie NULL. Retire sinon la référence trouvée de
//    l'ensemble et renvoie la référence trouvée.
extern void *set_remove(set *s, const void *ref);

//  set_pick : renvoie NULL si l'ensemble associé à s est vide. Renvoie sinon
//    l'une des références appartenant à l'ensemble.
extern void *set_pick(set *s);

//  set_is_empty : renvoie true ou false selon que l'ensemble associé à s est
//    vide ou non.
extern bool set_is_empty(set *s);

//  set_search : recherche dans l'ensemble associé à s la référence d'un objet
//    égal à celui de référence ref au sens de la fonction de comparaison. Si la
//    recherche est négative, renvoie NULL. Renvoie sinon la référence trouvée.
extern void *set_search(set *s, const void *ref);

//  set_card : renvoie le cardinal de l'ensemble associé à s.
extern size_t set_card(set *s);

//- EXTENSION ------------------------------------------------------------------

//  Pour savoir si le module gère l'extension, il suffit à son utilisateurice de
//    tester si la macroconstante SET_WANT_EXT est définie et si sa macro-
//    évaluation donne un entier qui n'est pas 0.

//  La macroconstante SET_WANT_EXT ainsi que les fonctions de l'extension
//    doivent se conformer aux spécifications 1) à 4).
//  1) Les fonctions de l'extension ne doivent être ni déclarées ni définies
//    lorsque la macroconstante SET_WANT_EXT n'est pas définie ou lorsqu'elle
//    est définie et que sa macro-évaluation donne l'entier 0.
//  2) Les fonctions de l'extension doivent être déclarées dans cette partie
//    interface du module et définies dans la partie implantation du module
//    lorsque la macroconstante SET_WANT_EXT est définie et que sa macro-
//    évaluation donne un entier qui n'est pas 0.
//  3) Si elle doit être définie, la macroconstante SET_WANT_EXT ne peut l'être
//    que par ce fichier en-tête, uniquement la première fois où celui-ci est
//    inclus et à la ligne 106.
//  4) Les fonctions de l'extension sont celles dont les spécifications et
//    prototypes figurent aux lignes 110-113.

#if defined SET_WANT_EXT
#error "Only <set.h> is allowed to define SET_WANT_EXT."
#endif

#define SET_WANT_EXT 1

#if defined SET_WANT_EXT && SET_WANT_EXT != 0

//  set_min : renvoie NULL si l'ensemble associé à s est vide. Recherche sinon
//    dans l'ensemble la référence d'un objet minimal au sens de la fonction de
//    comparaison. Renvoie la référence trouvée.
extern void *set_min(set *s);

#endif

//------------------------------------------------------------------------------

#endif
