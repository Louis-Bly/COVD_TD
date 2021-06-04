#pragma once

#include "ennemi.h"
#include "tools.h"
#include "grille.h"

class chemin
{
    point* direction;



    //Constructeur
    chemin();
    chemin(int nb_largeur_case, int nb_hauteur_case);


    //Fonction
    void Calcul_plus_court_chemin(); //Retourne une liste d'entier (haut, gauche, bas, droite)

};
