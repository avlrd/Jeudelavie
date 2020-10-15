/**
 *	\file grille.c
 *	fonctions liées aux grilles du jeu
 *	\author Arthur Villard
*/


#include "grille.h"

/**
 *	\fn void alloue_grille(int l, int c, grille* g)
 *	\param l nombre de ligne
 *	\param c nombre de colonnes
 *	\param g pointeur sur une grille
 *	\brief alloue une grille de taille l*c et initialise toute ses valeurs à 0 (cellule morte)
*/

void alloue_grille(int l, int c, grille* g)
{
	g->nbl = l;
	g->nbc = c;
	int i;
	g->cellules = (int**) malloc(l*sizeof(int*));
	for(i=0; i<l; i++)
		g->cellules[i] = (int*) calloc(c, sizeof(int));
}

/**
 *	\fn void libere_grille(grille* g)
 *	\param g pointeur sur une grille
 *	\brief liberation de grille
*/

void libere_grille(grille* g)
{
	int i;
	int l = g->nbl;
	for(i=0; i<l; i++)
		free(g->cellules[i]);
	free(g->cellules);
}

/**
 *	\fn void init_grille_from_file(char* filename, grille* g)
 *	\param filename pointeur sur un tableau de charactere (nom du fichier)
 *	\param g pointeur sur une grille
 *	\brief alloue et initialise une grille à partir d'un fichier 
*/

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/**
 *	\fn void copie_grille(grille gs, grille gd)
 *	\param gs une grille
 *	\param gd une grille
 *	\brief recopie gs dans gd
*/

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
