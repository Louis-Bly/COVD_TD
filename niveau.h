#pragma once

#include "interface.h"

#include <string>
using namespace std;



//Différents niveaux
bool tutoriel(int largeur_fenetre, int hauteur_fenetre, int taille_case);
bool niveau1(int largeur_fenetre, int hauteur_fenetre, int taille_case);
bool niveau2(int largeur_fenetre, int hauteur_fenetre, int taille_case);
bool niveau3(int largeur_fenetre, int hauteur_fenetre, int taille_case);
bool edition_de_niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case);

//Fonctionnement général d'un niveau
bool niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case, int nb_basique, int nb_ameliore, int nb_rapide, int nb_tank, int ecart_moyen, int argent_initial, int indice_arrivee, bool tutoriel=false);
