#pragma once

#include "tools.h"

class grille
{
    int taille_case;
    int nb_largeur_case;
    int nb_hauteur_case;
    bool* libre; //indique si une tour est présente sur la case i+j*nb_hauteur_case
public:
    //Constructeur
    grille(int l, int h, int taille_case_i);
    void affiche();
    int get_taille_case(){return taille_case;};
    int get_place(point pos);
    point get_pos(int place);
    void ajout_tour(int place);
};
