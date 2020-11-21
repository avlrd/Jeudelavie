/**
 *	\file grille.h
 *	header pour les fonctions liées aux grilles du jeu
 *	\author Arthur Villard
*/


#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct
	{
		int nbl; 
		int nbc; 
		int** cellules;
		int temps;
		int cyclique;
		int vieillissement;
	} grille;
 

// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/**
 *	\fn void alloue_grille(int l, int c, grille* g)
 *	\param l nombre de ligne
 *	\param c nombre de colonnes
 *	\param g pointeur sur une grille
 *	\brief alloue une grille de taille l*c et initialise toute ses valeurs à 0 (cellule morte)
 */
void alloue_grille (int l, int c, grille* g);

// libère une grille
/**
 *	\fn void libere_grille(grille* g)
 *	\param g pointeur sur une grille
 *	\brief liberation de grille
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/**
 *	\fn void init_grille_from_file(char* filename, grille* g)
 *	\param filename pointeur sur un tableau de charactere (nom du fichier)
 *	\param g pointeur sur une grille
 *	\brief alloue et initialise une grille à partir d'un fichier 
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
 *	\param i indice de la ligne de la cellule à rendre vivante
 *	\param j indice de la colonne de la cellule à rendre vivante
 *	\param g une grille
 *	\brief rend vivante la cellule (i, j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}

/**
 *	\param i indice de la ligne de la cellule à rendre morte
 *	\param j indice de la colonne de la cellule à rendre morte
 *	\param g une grille
 *	\brief rend morte la cellule (i, j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

/**
 *	\param i indice de la ligne de la cellule à rendre non-viable
 *	\param j indice de la colonne de la cellule à rendre non-viable
 *	\param g une grille
 *	\brief rend non-viable la cellule (i, j) de la grille g
 */
static inline void set_non_viable(int i, int j, grille g){g.cellules[i][j] = -1;}

// teste si la cellule (i,j) de la grille g est vivante
/**
 *	\param i indice de la ligne de la cellule à tester
 *	\param j indice de la colonne de la cellule à tester
 *	\param g une grille
 *	\brief teste si la cellule (i, j) est vivante ou non
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] > 0;}

// teste si la cellule (i,j) de la grille g est non_viable
/**
 *	\param i indice de la ligne de la cellule à tester
 *	\param j indice de la ligne de la cellule à tester
 *	\param g une grille
 *	\brief teste si la cellule (i, j) est non_viable ou non
 */
static inline int est_non_viable(int i, int j, grille g){return g.cellules[i][j] == -1;}

// recopie gs dans gd (sans allocation)
/**
 *	\fn void copie_grille(grille gs, grille gd)
 *	\param gs une grille
 *	\param gd une grille
 *	\brief recopie gs dans gd
 */
void copie_grille (grille gs, grille gd);

/**
 *	\fn int egalite_grille(grille *g, grille *gc);
 *	\param g une grille
 *	\param gc une grille
 *	\brief teste l'égalité de deux grilles
 */
int egalite_grille(grille *g, grille *gc);

/**
 *	\fn int null_grille(grille *g);
 *	\param g une grille
 *	\brief teste si une grille ne contient que des cellules mortes à l'instant ou elle est testée
 */
int null_grille(grille *g);

#endif