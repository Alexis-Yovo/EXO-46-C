#include <stdio.h>
#include <stdlib.h>

// === Définition des structures ===
typedef union {
    int iNombre;
    char cSigne;
} Type_valeur;

typedef struct Sommet {
    Type_valeur valeur;
    struct Sommet *fils_g, *fils_d;
} Sommet;

typedef Sommet *Arbre;

// === Fonctions de construction (nécessaires pour le test) ===
Arbre construire_feuille(int n) {
    Arbre a = malloc(sizeof(Sommet));
    a->valeur.iNombre = n;
    a->fils_g = NULL;
    a->fils_d = NULL;
    return a;
}

Arbre construire_noeud(char op, Arbre g, Arbre d) {
    Arbre a = malloc(sizeof(Sommet));
    a->valeur.cSigne = op;
    a->fils_g = g;
    a->fils_d = d;
    return a;
}

// === Fonctions ===
void infixe(Arbre tree) {
    if (!tree) return;
    if (!tree->fils_g && !tree->fils_d) {
        printf("%d", tree->valeur.iNombre);
        return;
    }
    printf("(");
    infixe(tree->fils_g);
    printf("%c", tree->valeur.cSigne);
    infixe(tree->fils_d);
    printf(")");
}

void prefixe(Arbre tree) {
    if (!tree) return;
    if (!tree->fils_g && !tree->fils_d) {
        printf("%d", tree->valeur.iNombre);
        return;
    }
    printf("%c", tree->valeur.cSigne);
    prefixe(tree->fils_g);
    prefixe(tree->fils_d);
}

void postfixe(Arbre tree) {
    if (!tree) return;
    if (!tree->fils_g && !tree->fils_d) {
        printf("%d ", tree->valeur.iNombre);
        return;
    }
    postfixe(tree->fils_g);
    postfixe(tree->fils_d);
    printf("%c ", tree->valeur.cSigne);
}


int main() {
    // Construction de l'arbre : (12+15)*((7*10)-3)
    Arbre a = construire_noeud('*',
        construire_noeud('+', construire_feuille(12), construire_feuille(15)),
        construire_noeud('-',
            construire_noeud('*', construire_feuille(7), construire_feuille(10)),
            construire_feuille(3)
        )
    );

    printf("➡️  Infixe   : ");
    infixe(a);
    printf("\n");

    printf("➡️  Préfixe  : ");
    prefixe(a);
    printf("\n");

    printf("➡️  Postfixe : ");
    postfixe(a);
    printf("\n");

    return 0;
}
