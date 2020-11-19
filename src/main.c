/**
 *	\file main.c
 *	fonction main
 *	\author Arthur Villard
*/


#include <stdio.h>
#include "grille.h"
#include "io.h"
#include "jeu.h"

/**
 *	\fn int main(int argc, char** argv)
 *	\param argc
 *	\param argv pointeur sur un tableau de charactere (nom de fichier)
 *	\brief fonction main
*/

int main (int argc, char ** argv) {
	
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	//affiche_grille(g);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
