#pragma once

#include "ennemi.h"
#include "tools.h"

class chemin
{

    int taille_carre_grille; //pour controler le deplacement (eviter de se deplacer sur la position d'une tour)
    int nb_largeur_case;
    int nb_hauteur_case;
    bool* libre; //indique si une tour est présente sur la case i+j*nb_hauteur_case

    //Constructeur
    chemin(int l, int h, int taille_case);

    //Fonction
    void Calcul_plus_court_chemin(); //Retourne une liste d'entier (haut, gauche, bas, droite)

};
