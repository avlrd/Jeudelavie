/**
 *	\file grille.c
 *	\brief fonctions liées aux grilles du jeu
 *	\author Arthur Villard
 */


#include "grille.h"

void alloue_grille(int l, int c, grille* g)
{
	g->nbl = l;
	g->nbc = c;
	g->temps=0;
	g->cellules = (int**) malloc(l*sizeof(int*));
	if(g->cellules==NULL)
		return exit(1);
	for(int i=0; i<l; i++)
	{
		g->cellules[i] = (int*) calloc(c, sizeof(int));
		if(g->cellules==NULL)
			return exit(1);
	}
}

void libere_grille(grille* g)
{
	int l = g->nbl;
	for(int i=0; i<l; i++)
		free(g->cellules[i]);
	free(g->cellules);
}

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0, non_viables=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & non_viables);
	for (n=0; n< non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_non_viable(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

int egalite_grille(grille *g, grille *gc)
{
	int check = 1;
	int i=0, j=0;

	while(i<g->nbl)
	{
		j=0;
		while((j<g->nbc) && (check ==1))
		{
			if(g->cellules[i][j] != gc->cellules[i][j])
				check = 0;
			j++;
		}
		i++;
	}
	return check;
}

int null_grille(grille *g)
{
	int check = 1;
	int i=0, j=0;

	while(i<g->nbl)
	{
		j=0;
		while((j<g->nbc) && (check == 1))
		{
			if(est_vivante(i, j, *g))
				check = 0;
			j++;
		}
		i++;
	}
	return check;
}