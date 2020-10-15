/**
 * 	\file io.C
 *	fonctions d'entrée et sortie
 *	\author Arthur Villard
*/


#include "io.h"

/**
 *	\fn void affiche_trait (int c)
 *	\param c nombre de colonnes
 *	\brief affichage d'un trait horizontal
*/
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 *	\fn void affiche_ligne (int c, int* ligne)
 *	\param c nombre de colonnes
 *	\param ligne pointeur vers un tableau
 *	\brief affichage d'une ligne de la grille
*/

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

/**
 *	\fn void affiche_grille (grille g)
 *	\param g une grille
 *	\brief affichage d'une grille
*/

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

/**
 *	\fn void efface_grille (grille g)
 *	\param g une grille
 *	\brief effacement d'une grille
*/

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5); 
}

/**
 *	\fn void debut_jeu(grille *g, grille *gc)
 *	\param g pointeur sur une grille
 *	\param gc pointeur sur une grille (copie)
 *	\brief fonction qui débute le jeu
*/

void debut_jeu(grille *g, grille *gc){
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}

			case 'n' :
			{ // touche "n" pour créer une nouvelle grille

				char newgrille[30];

				printf("Entrez le nom de la nouvelle grille :");
				scanf("%s", &newgrille);
				printf("%s", newgrille);
				libere_grille(g);
				libere_grille(gc);

				init_grille_from_file(newgrille, g);

				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				break;
			}

			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
