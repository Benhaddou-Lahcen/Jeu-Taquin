#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "Header.h"
#include <iostream>
#include <random>

List listeNoeuds;
List NoeudsDejaTraites;

void Insererprecesseur(Etat nouveauetat, List* pliste, noeud* nprecesseur) {
    List L1 = *pliste;
    noeud* nouveaunoeaud = new(noeud);
    nouveaunoeaud->etat = nouveauetat;
    nouveaunoeaud->suivant = NULL;
    nouveaunoeaud->precesseur = nprecesseur;
    if (L1.debut == NULL) {
        L1.debut = nouveaunoeaud;
        L1.fin = nouveaunoeaud;
    }
    else {
        (L1.fin)->suivant = nouveaunoeaud;
        (L1.fin) = nouveaunoeaud;
    }
    *pliste = L1;
}

void Inserer(noeud* noe, List* pliste) {
    Etat nouveauetat = noe->etat;
    noeud* nprecesseur = noe->precesseur;
    Insererprecesseur(nouveauetat, pliste, nprecesseur);
}

void Insereretat(Etat nouveauetat, List* pliste) {
    noeud* nprecesseur = NULL;
    Insererprecesseur(nouveauetat, pliste, nprecesseur);
}

noeud* Extraire(List* listenoeuds) {
    noeud* temp;
    if (listenoeuds->debut == listenoeuds->fin) listenoeuds->fin = NULL;
    temp = (listenoeuds->debut);
    listenoeuds->debut = temp->suivant;
    return temp;
}

int etatSolution(Etat etatCourant, Etat etatFinal) {
    int estEgal = 1;
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (etatCourant.tableau[i][j] != etatFinal.tableau[i][j]) {
                estEgal = 0;
                break;
            }
        }
        if (!estEgal) {
            break;
        }
    }
    return (estEgal);
}

void regle1(noeud* noeudCourant, List* liste) {
    int i, j;
    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            if (noeudCourant->etat.tableau[i][j] == 0 && i != 0) {
                Etat nouvelEtat = noeudCourant->etat;
                nouvelEtat.tableau[i][j] = nouvelEtat.tableau[i - 1][j];
                nouvelEtat.tableau[i - 1][j] = 0;
                nouvelEtat.g = (noeudCourant->etat).g + 1;
                Insererprecesseur(nouvelEtat, liste, noeudCourant);
            }
        }
    }
}

void regle2(noeud* noeudCourant, List* liste) {
    int i, j;
    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            if (noeudCourant->etat.tableau[i][j] == 0 && i != TAILLE_GRILLE - 1) {
                Etat nouvelEtat = noeudCourant->etat;
                nouvelEtat.tableau[i][j] = nouvelEtat.tableau[i + 1][j];
                nouvelEtat.tableau[i + 1][j] = 0;
                nouvelEtat.g = (noeudCourant->etat).g + 1;
                Insererprecesseur(nouvelEtat, liste, noeudCourant);
            }
        }
    }
}

void regle3(noeud* noeudCourant, List* liste) {
    int i, j;
    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            if (noeudCourant->etat.tableau[i][j] == 0 && j != TAILLE_GRILLE - 1) {
                Etat nouvelEtat = noeudCourant->etat;
                nouvelEtat.tableau[i][j] = nouvelEtat.tableau[i][j + 1];
                nouvelEtat.tableau[i][j + 1] = 0;
                nouvelEtat.g = noeudCourant->etat.g + 1;
                Insererprecesseur(nouvelEtat, liste, noeudCourant);
            }
        }
    }
}

void regle4(noeud* noeudCourant, List* liste) {
    int i, j;
    for (i = 0; i < TAILLE_GRILLE; i++) {
        for (j = 0; j < TAILLE_GRILLE; j++) {
            if (noeudCourant->etat.tableau[i][j] == 0 && j != 0) {
                Etat nouvelEtat = noeudCourant->etat;
                nouvelEtat.tableau[i][j] = nouvelEtat.tableau[i][j - 1];
                nouvelEtat.tableau[i][j - 1] = 0;
                nouvelEtat.g = noeudCourant->etat.g + 1;
                Insererprecesseur(nouvelEtat, liste, noeudCourant);
            }
        }
    }
}

void genererSuccesseurs(noeud* noeudCourant, List* liste) {
    regle1(noeudCourant, liste);
    regle2(noeudCourant, liste);
    regle3(noeudCourant, liste);
    regle4(noeudCourant, liste);
}

int g(noeud* n) {
    return (n->etat).g;
}

int h(noeud* n, Etat etatFinal) {
    Etat etatCourant = n->etat;
    int h = 0;
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (etatCourant.tableau[i][j] != etatFinal.tableau[i][j]) {
                h++;
            }
        }
    }
    return h;
}

int f(noeud* n, Etat etatFinal) {
    return h(n, etatFinal) + g(n);
}

int Appartient(noeud* n, List listeNoeuds) {
    Etat e = n->etat;
    noeud* courant = listeNoeuds.debut;
    while (courant != NULL) {
        int estEgal = 1;
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                if ((courant->etat).tableau[i][j] != e.tableau[i][j]) {
                    estEgal = 0;
                    break;
                }
            }
            if (!estEgal) {
                break;
            }
        }
        if (estEgal) {
            return 1;
        }
        courant = courant->suivant;
    }
    return 0;
}

noeud* NoeudAppartient(Etat e, List listeNoeuds) {
    noeud* courant = listeNoeuds.debut;
    while (courant != NULL) {
        int estEgal = 1;
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                if ((courant->etat).tableau[i][j] != e.tableau[i][j]) {
                    estEgal = 0;
                    break;
                }
            }
            if (!estEgal) {
                break;
            }
        }
        if (estEgal) {
            return courant;
        }
        courant = courant->suivant;
    }
    return 0;
}

void Supprimer(noeud* n, List* NoeudsDejaTraites) {
    Etat* etat = &(n->etat);
    noeud* courant = NoeudsDejaTraites->debut;
    noeud* precedent = NULL;
    while (courant != NULL) {
        int estEgal = 1;
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                if ((courant->etat).tableau[i][j] != etat->tableau[i][j]) {
                    estEgal = 0;
                    break;
                }
            }
            if (!estEgal) {
                break;
            }
        }
        if (estEgal) {
            if (precedent == NULL) {
                NoeudsDejaTraites->debut = courant->suivant;
                free(courant);
                return;
            }
            else {
                precedent->suivant = courant->suivant;
                free(courant);
                return;
            }
        }
        precedent = courant;
        courant = courant->suivant;
    }
}

void Remplacer(noeud* ancienNoeud, List* liste, noeud* nouveauNoeud) {
    noeud* courant = liste->debut;
    noeud* precedent = NULL;
    while (courant != NULL) {
        if (courant == ancienNoeud) {
            if (precedent == NULL) {
                liste->debut = nouveauNoeud;
            }
            else {
                precedent->suivant = nouveauNoeud;
            }
            nouveauNoeud->suivant = ancienNoeud->suivant;
            free(ancienNoeud);
            return;
        }
        precedent = courant;
        courant = courant->suivant;
    }
}

void Tri(List* liste, Etat etatFinal) {
    if (liste == NULL || liste->debut == NULL || liste->debut->suivant == NULL) {
        return;
    }
    int c = 0;
    noeud* i, * j, * min, * temp;
    noeud* precedentmin = NULL, * precedenti, * precedentj;
    precedenti = NULL;
    i = liste->debut;
    while (i != NULL) {
        min = i;
        precedentj = i;
        j = precedentj->suivant;
        while (j != NULL) {
            if (f(j, etatFinal) < f(min, etatFinal)) {
                min = j;
                precedentmin = precedentj;
            }
            precedentj = j;
            j = j->suivant;
        }
        if (min != i) {
            if (min->suivant == NULL) liste->fin = i;
            if (i == liste->debut) {
                liste->debut = min;
            }
            else {
                precedenti->suivant = min;
            }
            temp = min->suivant;
            if (precedentmin != i) {
                precedentmin->suivant = i;
                min->suivant = i->suivant;
                i->suivant = temp;
            }
            else {
                min->suivant = i;
                i->suivant = temp;
            }
        }
        i = liste->debut;
        for (int j = 0; j < c; j++) { i = i->suivant; }
        precedenti = i;
        i = i->suivant;
        c++;
    }
}

void afficherMatrice(int matrice[TAILLE_GRILLE][TAILLE_GRILLE], int c) {
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            printf(" %d ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("_________\n");
}

void afficherchemin(noeud* n) {
    noeud* current = n;
    while (current != NULL) {
        afficherMatrice(current->etat.tableau, current->etat.g);
        current = current->precesseur;
        if (current != NULL) printf("   /\\\n   ||\n");
    }
}

void afficherlist(List L1, Etat etatFinal) {
    noeud* current = L1.debut;
    while (current != NULL) {
        afficherMatrice(current->etat.tableau, f(current, etatFinal));
        current = current->suivant;
    }
    printf("*********************\n");
}

noeud* RechercheAetoile(Etat etatInitial, Etat etatFinal) {
    List listeSuccesseurs;
    listeNoeuds.debut = listeNoeuds.fin = NULL;
    NoeudsDejaTraites.debut = NoeudsDejaTraites.fin = NULL;
    Etat etatCourant;
    noeud* noeudCourantp;
    Insereretat(etatInitial, &listeNoeuds);
    int C, C0;
    while (listeNoeuds.debut != NULL) {
        noeudCourantp = Extraire(&listeNoeuds);
        etatCourant = noeudCourantp->etat;
        listeSuccesseurs.debut = listeSuccesseurs.fin = NULL;
        if (etatSolution(etatCourant, etatFinal)) {
            while (noeudCourantp->precesseur != NULL) {
                if ((noeudCourantp->precesseur)->precesseur == NULL) {
                    return noeudCourantp;
                }
                noeudCourantp = noeudCourantp->precesseur;
            }
            if (noeudCourantp->precesseur == NULL) {
                return noeudCourantp;
            }
        }
        else {
            genererSuccesseurs(noeudCourantp, &listeSuccesseurs);
            for (noeud* n = listeSuccesseurs.debut; n != NULL; n = n->suivant) {
                C = f(n, etatFinal);
                if (!Appartient(n, listeNoeuds) && !Appartient(n, NoeudsDejaTraites)) {
                    Inserer(n, &listeNoeuds);
                }
                else {
                    noeud* nC0 = new(noeud);
                    if (Appartient(n, listeNoeuds)) {
                        nC0 = NoeudAppartient(n->etat, listeNoeuds);
                        C0 = f(nC0, etatFinal);
                        if (C < C0) {
                            Remplacer(nC0, &listeNoeuds, n);
                        }
                    }
                    else if (Appartient(nC0, NoeudsDejaTraites)) {
                        if (C < C0) {
                            Supprimer(nC0, &NoeudsDejaTraites);
                            Inserer(n, &listeNoeuds);
                        }
                    }
                }
            }
            Insereretat(etatCourant, &NoeudsDejaTraites);
            Tri(&listeNoeuds, etatFinal);
        }
    }
}
