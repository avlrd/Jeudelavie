/**
 *	\file io.h
 *	header pour les fonctions d'entrée et sortie
 *	\author Arthur Villard
 */


#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"
#define max_length 128

// affichage d'un trait horizontal
/**
 *	\fn void affiche_trait (int c)
 *	\param c nombre de colonnes
 *	\brief affichage d'un trait horizontal
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
 *	\fn void affiche_ligne (int c, int* ligne)
 *	\param c nombre de colonnes
 *	\param ligne pointeur vers un tableau
 *	\brief affichage d'une ligne de la grille
*/
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/**
 *	\fn void affiche_grille (grille g)
 *	\param g une grille
 *	\brief affichage d'une grille
*/
void affiche_grille (grille g);

// effacement d'une grille
/**
 *	\fn void efface_grille (grille g)
 *	\param g une grille
 *	\brief effacement d'une grille
*/
void efface_grille (grille g);

// debute le jeu
/**
 *	\fn void debut_jeu(grille *g, grille *gc)
 *	\param g pointeur sur une grille
 *	\param gc pointeur sur une grille (copie)
 *	\brief Débute le jeu : \n \b q pour quitter \n \b entrée pour évoluer \n \b n pour une nouvelle grille \n \b c pour activer/désactiver le voisinage cyclique \n \b v pour activer/désactiver le vieillissement
*/
void debut_jeu(grille *g, grille *gc);

#endif
