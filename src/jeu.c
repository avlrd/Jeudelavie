/**
 *	\file jeu.c
 *	fonctionnement du jeu
 *	\author Arthur Villard
 */


#include "jeu.h"

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



int compte_voisins_vivants_nc(int i, int j, grille g){
	int v = 0, l = g.nbl, c = g.nbc;
	for(int li = i-1; li <= i+1; li++)
	{
		for(int cj = j-1; cj <= j+1; cj++)
		{
			if (cj != -1 && cj != c && li != -1 && li != l && (li != i || cj != j))
				v += est_vivante(li, cj, g);
		}
	}
	return v; 
}


void evolue (grille *g, grille *gc)
{
	copie_grille (*g,*gc); // copie temporaire de la grille
	g->temps++;

	int (*compte_voisins_vivants_fct) (int, int, grille);
	if(g->cyclique)
		compte_voisins_vivants_fct = &compte_voisins_vivants;
	else
		compte_voisins_vivants_fct = &compte_voisins_vivants_nc;

	int i, j, l = g->nbl, c = g->nbc, v;

	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = compte_voisins_vivants_fct(i, j, *gc);
			if (est_vivante(i,j,*gc)) 
			{ // evolution d'une cellule vivante
				if ((v!=2 && v!= 3) || g->cellules[i][j]>=8)
					set_morte(i,j,*g);

				else if(g->vieillissement)
					(g->cellules[i][j])++;
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}
