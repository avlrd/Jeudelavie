/**
 * 	\file io.C
 *	fonctions d'entrée et sortie
 *	\author Arthur Villard
*/

#include "io.h"

void affiche_trait (int c)
{
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne)
{
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]);
	printf("|\n");
	return;
}

void affiche_grille (grille g)
{
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	printf("\nMode cyclique : ");
	if(!g.cyclique)
		printf("désactivé\n");
	else
		printf("activé\n");

	printf("\nMode vieillissement : ");
	if(!g.vieillissement)
		printf("désactivé\n");
	else
		printf("activé\n");

	printf("\nTemps d'évolution de la grille : %d \n\n", g.temps);
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g)
{
	system("clear"); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	g->temps = 0;
	g->cyclique = 1;
	g->vieillissement = 1;
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
				char newgrille[max_length];
				libere_grille(g);
				libere_grille(gc);

				printf("Entrez le chemin d'accès de la nouvelle grille : ");
				scanf("%s", newgrille);
				init_grille_from_file(newgrille, g);
				alloue_grille(g->nbl, g->nbc, gc);
				affiche_grille(*g);
				while(getchar() != '\n');
				break;
			}

			case 'c' :
			{ // touche c pour alterner entre mode cyclique et non cyclique
				cyclique = !(cyclique);
				break;
			}

			case 'v' :
			{ // touche v pour activer / désactiver le vieillissement
				vieillissement = !(vieillissement);
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
