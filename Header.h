#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define TAILLE_GRILLE 3



typedef struct {
    int tableau[TAILLE_GRILLE][TAILLE_GRILLE];
    int g;
} Etat;

typedef struct Noeud {
    Etat etat;
    struct Noeud* precesseur;
    struct Noeud* suivant;
} noeud;

typedef struct {
    noeud* debut;
    noeud* fin;
} List;


void Insererprecesseur(Etat nouveauetat, List* pliste, noeud* nprecesseur);
void Inserer(noeud* noe, List* plistle);
void Insereretat(Etat nouveauetat, List* pliste);
noeud* Extraire(List* listenoeuds);
int etatSolution(Etat etatCourant, Etat etatFinal);
void regle1(noeud* noeudCourant, List* liste);
void regle2(noeud* noeudCourant, List* liste);
void regle3(noeud* noeudCourant, List* liste);
void regle4(noeud* noeudCourant, List* liste);
void genererSuccesseurs(noeud* noeudCourant, List* liste);
int g(noeud* n);
int h(noeud* n, Etat etatFinal);
int f(noeud* n, Etat etatFinal);
int Appartient(noeud* n, List listeNoeuds);
noeud* NoeudAppartient(Etat e, List listeNoeuds);
void Supprimer(noeud* n, List* NoeudsDejaTraites);
void Remplacer(noeud* ancienNoeud, List* liste, noeud* nouveauNoeud);
void Tri(List* liste, Etat etatFinal);
noeud *RechercheAetoile(Etat etatInitial, Etat etatFinal);
void afficherMatrice(int matrice[TAILLE_GRILLE][TAILLE_GRILLE], int c);
void afficherListe(List L1);
void afficherchemin(noeud* n);



#endif // HEADER_H_INCLUDED
