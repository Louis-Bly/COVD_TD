#pragma once

#include "tools.h"

class grille
{
    int taille_case;
    int nb_largeur_case;
    int nb_hauteur_case;
    bool* libre_tour; //indique si une tour ou un ennemi est présente sur la case i+j*nb_hauteur_case (on ne peut pas placer une tour sur une case ou un ennemi est présent)
    bool* libre_ennemi; //indique si une tour est présente sur la case i+j*nb_hauteur_case (2 ennemis peuvent être sur une même case)
//    int* cout_des_cases;

public:
    //Constructeur
    grille(int l, int h, int taille_case_i);



    void affiche();

    void ajout_tour(int place);
//    void maj_cout_des_cases();

    // Fonctions get
    bool get_libre_ennemi(int indice){return libre_ennemi[indice];};
//    int get_cout_des_cases(int indice){return cout_des_cases[indice];};
    bool get_libre_tour(int indice){return libre_tour[indice];};
    int get_taille_case(){return taille_case;};    
    int get_nombre_case(){return nb_largeur_case*nb_hauteur_case;};
    int get_nb_largeur_case(){return nb_largeur_case;};
    int get_nb_hauteur_case(){return nb_hauteur_case;};

    void set_libre_ennemi(int i,bool b){libre_ennemi[i]=b;};

    int get_place(point pos);
    point get_pos(int place);

    point get_indices_xy(int place);
    int get_indices(point xy);





};
