#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include "ennemi.h"
#include "interface.h"
#include "chemin.h"
#include "grille.h"
#include "tour.h"
#include "projectile.h"
#include "menu_principal.h"

#include <string>
using namespace std;

//Fonctionnement général du niveau


//Différents niveaux
void tutoriel(int largeur_fenetre, int hauteur_fenetre, int taille_case);
void niveau1(int largeur_fenetre, int hauteur_fenetre, int taille_case);
void niveau2(int largeur_fenetre, int hauteur_fenetre, int taille_case);
void niveau3(int largeur_fenetre, int hauteur_fenetre, int taille_case);
void niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case, int nb_basique, int nb_ameliore, int nb_rapide, int nb_tank, int ecart_moyen, int argent_initial, int indice_arrivee, bool tutoriel=false);
