#pragma once

#include "grille.h"

class chemin
{
    point* direction;
    int* chemin_de_ennemi;
    int taille_chemin;

public:
    int get_taille_chemin(){return taille_chemin;};
    int get_chemin_de_ennemi(int i){return chemin_de_ennemi[i];};

    void set_taille_chemin(int taille){taille_chemin=taille;};
    //Constructeur
    chemin();
    chemin(grille G);

    //Destructeur
    ~chemin();


    //Fonction

    //void maj_cout_des_cases(grille Grille);

    bool Calcul_plus_court_chemin(point position,grille Grille, point arrivee); //Retourne une liste de points (haut, gauche, bas, droite)

};
