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

int oscillante(grille g, int x)
{
	int i=0, j=1;
	grille copie, test, tmp;

	alloue_grille(g.nbl, g.nbc, &copie);
	copie_grille(g, copie);
	alloue_grille(g.nbl, g.nbc, &test);

	for(i=0; i<x; i++)
		evolue(&copie, &test);

	i=0;

	alloue_grille(g.nbl, g.nbc, &tmp);
	copie_grille(copie, tmp);

	while((j<MAX_O) && (i==0))//OSCILL_MAX dans grille.h
	{
		evolue(&copie, &test);
		if(egalite_grille(&tmp, &copie) == 1)
			i = j;
		j++;
	}

	if(null_grille(&g) == 1)
		i = -1;

	libere_grille(&copie);
	libere_grille(&test);
	libere_grille(&tmp);

	return i;
}

int oscillante_delai(grille g)
{
	int i, j, check=0;

	grille copie, tmp;
	alloue_grille(g.nbl, g.nbc, &tmp);
	alloue_grille(g.nbl, g.nbc, &copie);
	copie_grille(g, copie);

	for(i=0; (i<MAX_OI) && (check==0); i++)
	{
		j = oscillante(copie, 0);
		if(j != 0)
			check = 1;
		evolue(&copie, &tmp);
	}

	libere_grille(&tmp);
	libere_grille(&copie);
	
	if(j == -1)
		return -1;
	if(check == 1)
		return i-1;
	return i;
}

void evolue (grille *g, grille *gc)
{
	copie_grille(*g, *gc); // copie temporaire de la grille
	g->temps++;

	int (*compte_voisins_vivants_fct) (int, int, grille);
	if(g->cyclique)
		compte_voisins_vivants_fct = &compte_voisins_vivants;
	else
		compte_voisins_vivants_fct = &compte_voisins_vivants_nc;

	int i, j, l = g->nbl, c = g->nbc, v;

	for (i=0; i<l; i++)
	{
		for (j=0; j<c; j++)
		{
			v = compte_voisins_vivants_fct(i, j, *gc);
			if (est_vivante(i, j, *g)) 
			{ // evolution d'une cellule vivante
				if ((v!=2 && v!= 3) || g->cellules[i][j]>=8)
					set_morte(i, j, *g);

				else if(g->vieillissement)
					(g->cellules[i][j])++;
			}
			else 
			{ // evolution d'une cellule morte
				if ((v==3) && !est_non_viable(i, j, *g)) set_vivante(i, j, *g);
			}
		}
	}
	return;
}
