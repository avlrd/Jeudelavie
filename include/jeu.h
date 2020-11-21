/**
 *	\file jeu.h
 *	header pour les fonctions principales du jeu
 *	\author Arthur Villard
 */


#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#define MAX_O 1000
#define MAX_OI 1000

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
 *	\fn static inline int modulo(int i, int m) {return (i+m)%m;}
 *	\param i indice de la ligne/colonne concernee par le calcul
 *	\param m nombre de cellule dans la ligne/colonne
 *	\brief modification du modulo pour traiter correctement les cas i=0 et j=0 dans le calcul des voisins avec bords cycliques
 */
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
 *	\fn int compte_voisins_vivants_nc(int i, int j, grille g)
 *	\param i entier
 *	\param j entier
 *	\param g une grille
 *	\brief compte le nombre de voisins vivants de façon cyclique
 */
int compte_voisins_vivants(int i, int j, grille g);

//compte le nombre de voisins vivants de la cellule (i, j)
//les bords sont non-cycliques
/**
 *	\fn int compte_voisins_vivants_nc(int i, int j, grille g)
 *	\param i entier
 *	\param j entier
 *	\param g une grille
 *	\brief compte le nombre de voisins vivants de façon non cyclique
 */
int compte_voisins_vivants_nc(int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
/** 
 *	\fn void evolue(grille *g, grille *gc)
 *	\param g pointeur vers une grille
 *	\param gc pointeur vers une grille (copie)
 *	\brief fait évoluer la grille g d'un pas dans le temps
 */
void evolue (grille *g, grille *gc);

/**
 *	\fn int oscillante(grille g, int x):
 *	\param g une grille
 *	\param x un entier
 *	\brief teste si une grille est oscillante ou pas et donne sa période
 */
int oscillante(grille g, int x);

/**
 *	\fn int oscillante_indirecte(grille g)
 *	\param g une grille
 *	\brief retourne le nombre de pas avant la période
 */
int oscillante_delai(grille g);

#endif