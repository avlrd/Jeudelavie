/**
 *	\brief déclarations de fonctions de cairo.c
 *	\file cairo.h
 *	\author Arthur Vilard
 */

#ifndef __CAIRO_H__
#define __CAIRO_H__

#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "jeu.h"

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define SIZEX 1500
#define SIZEY 1500
#define SIZECELL 30
#define MOVX 20
#define MOVY 100
#define max_length 128

/**
 *	\fn affiche_grille_gui(cairo_surface_t *surface, grille g)
 *	\param surface surface cairo (pointeur)
 *	\param g une grille
 *	\brief affiche une grille en mode gui
 */

 void affiche_grille_gui(cairo_surface_t *surface, grille g);

/**
 *	\fn debut_jeu_gui(grille *g, grille *gc)
 *	\param g une grille
 *	\param gc une grille
 *	\brief débute le jeu dans sa versio gui
 */

 void debut_jeu_gui(grille *g, grille *gc);

 #endif