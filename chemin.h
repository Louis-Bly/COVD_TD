#pragma once

#include "tools.h"
#include "grille.h"

class chemin
{
    point* direction;
    int* cout_des_cases;


public:
    //Constructeur
    chemin();
    chemin(grille G);


    //Fonction
    void maj_cout_des_cases(grille Grille);

    void Calcul_plus_court_chemin(point position,grille Grille); //Retourne une liste de points (haut, gauche, bas, droite)

};
