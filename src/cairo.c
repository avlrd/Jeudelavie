/**
 *	\file cairo.c
 *	\brief Affichage graphique
 *	\author Arthur Villard
 */

#include "cairo.h"

void affiche_grille_gui(cairo_surface_t *surface, grille g)
{
	//create cairo mask
	cairo_t *cr;
	cr = cairo_create(surface);

	//background
	cairo_set_source_rgb(cr, 0.1, 0.1, 0.1);
	cairo_paint(cr);

	int l = g.nbl;
	int c = g.nbc;

	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);

	for(int i = 0; i <= l; i++)
	{
		cairo_move_to(cr, MOVX, MOVY + (i*SIZECELL));
		cairo_line_to(cr, MOVX + (c*SIZECELL), MOVY + (i*SIZECELL));
		cairo_set_line_width(cr, 1);
		cairo_stroke(cr);
	}

	for(int i = 0; i <= c; i++)
	{
		cairo_move_to(cr, MOVX + (i*SIZECELL), MOVY);
		cairo_line_to(cr, MOVX + (i*SIZECELL), MOVY + (l*SIZECELL));
		cairo_set_line_width(cr, 1);
		cairo_stroke(cr);
	}

	//vivant
	for(int i = 0; i < l; i++)
	{
		for(int j = 0; j < c; j++)
		{
			if(est_non_viable(i, j, g))
			{
				cairo_rectangle(cr, MOVX + (j*SIZECELL)+1, MOVY + (i*SIZECELL)+1, SIZECELL-2, SIZECELL-2);
				cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
				cairo_fill(cr);
			}
			else if(est_vivante(i, j, g))
			{
				int tmp = (g.cellules[i][j]-1);
				cairo_rectangle(cr, MOVX + (j*SIZECELL)+1, MOVY + (i*SIZECELL)+1, SIZECELL-2, SIZECELL-2);
				cairo_set_source_rgb(cr, (float) (tmp/8.0f), (float) 1-(tmp/8.0f), 0.0);
				cairo_fill(cr);
			}
		}
	}
	cairo_destroy(cr); //destroy cairo surface
}

void debut_jeu_gui(grille *g, grille *gc)
{
	//X11 display

	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int src;
	int quit = 0;
	g->cyclique = 1;
	g->vieillissement = 1;
	g->temps = 0;
	char str[12];
	KeySym key;
	char keychar[8];

	//init display

	if(!(dpy = XOpenDisplay(NULL)))
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	src = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, src);

	win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, BlackPixel(dpy, src), BlackPixel(dpy, src));

	XStoreName(dpy, win, "Jeu de la Vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask);
	XMapWindow(dpy, win);

	//create cairo surface

	cairo_surface_t *cs;
	cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	//run the event loop

	while(quit == 0)
	{
		sprintf(str, "%d", g->temps);
		affiche_grille_gui(cs, *g);
		cairo_t *cr = cairo_create(cs);
		cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
		cairo_set_font_size(cr, 15);
		cairo_set_source_rgb(cr, 1, 1, 1);
		cairo_move_to(cr, MOVX, MOVY-20);
		cairo_show_text(cr, "Temps d'évolution : ");
		cairo_show_text(cr, str);
		cairo_show_text(cr, "Mode cyclique : ");
		(g->cyclique == 0?cairo_show_text(cr, "desactivé"):cairo_show_text(cr, "activé"));
		cairo_show_text(cr, "Mode vieillissement : ");
		(g->vieillissement == 0?cairo_show_text(cr, "desactivé"):cairo_show_text(cr, "activé"));
		cairo_destroy(cr);

		XNextEvent(dpy, &e);
		switch(e.type)
		{
			case ButtonPress:
			{
				switch(e.xbutton.button)
				{
					case Button1:
					{
						evolue(g, gc);
						g->temps++;
						break;
					}
					case Button3:
					{
						quit = 1;
						break;
					}
				}
			}

			case KeyPress:
			{
				XLookupString(&e.xkey, keychar, sizeof(keychar), &key, NULL);
				switch(key)
				{
					case 65293:
					{
						evolue(g, gc);
						break;
					}

					case 'n':
					{
						cairo_t *cr = cairo_create(cs);
						cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
						cairo_set_font_size(cr, 15);
						cairo_set_source_rgb(cr, 1, 1, 1);
						cairo_move_to(cr, MOVX, MOVY-60);
						cairo_show_text(cr, "Entrez le chemin d'accès de la nouvelle grille : ");
						XNextEvent(dpy, &e);
						cairo_destroy(cr);
						char newgrille[max_length];
						printf("Path : ");
						scanf("%s", newgrille);
						libere_grille(g);
						libere_grille(gc);
						init_grille_from_file(newgrille, g);
						alloue_grille(g->nbl, g->nbc, gc);
						break;
					}

					case 'c':
					{
						g->cyclique =! g->cyclique;
						break;
					}

					case 'v':
					{
						g->vieillissement =! g->vieillissement;
						break;
					}

					case 'q':
					{
						quit = 1;
						break;
					}
				}
			}
		}
	}
	cairo_surface_destroy(cs); //destroy surface
	XCloseDisplay(dpy); //close display
	return;
}