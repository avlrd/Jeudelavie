/**
 *	\file jeu.c
 *	fonctionnement du jeu
 *	\author Arthur Villard
*/


#include "jeu.h"
#include <stdbool.h>

extern bool cyclique;


int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 *	\fn int compte_voisins_vivants_nc(int i, int j, grille g)
*/

int compte_voisins_vivants_nc(int i, int j, grille g){
	int v=0, l=g.nbl, c = g.nbc;

		v+= (i>0&&j>0) ? est_vivante(i-1,j-1,g) : 0;
		v+= (i>0) ? est_vivante(i-1,j,g) : 0;
		v+= (i>0&&j>c-1) ? est_vivante(i-1,j+1,g) : 0;
		v+= (j>0) ? est_vivante(i,j-1,g) : 0;
		v+= (j<c-1) ? est_vivante(i,j+1,g) : 0;
		v+= (i<l-1&&j>0) ? est_vivante(i+1,j-1,g) : 0;
		v+= (i<l-1) ? est_vivante(i+1,j,g) : 0;
		v+= (i<l-1&&j<c-1) ? est_vivante(i+1,j+1,g) : 0;

	
	return v; 
}

/** 
 *	\fn void evolue(grille *g, grille *gc)
 *	\param g pointeur vers une grille
 *	\param gc pointeur vers une grille (copie)
 *	\brief fait évoluer la grille g d'un pas dans le temps
 */

void evolue (grille *g, grille *gc, int vieillissement, int (*fonction) (int, int, grille))
{
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = fonction(i, j, *gc);
			if (est_vivante(i,j,*gc)) 
			{ // evolution d'une cellule vivante
				if ((g->cellules[i][j] >= 8 && vieillissement) || (v!=2 && v!=3)) set_morte(i,j,*g);

				else g->cellules[i][j]= g->cellules[i][j]+ 1;
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
