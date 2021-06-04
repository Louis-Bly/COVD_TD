#pragma once
#include "tools.h"
#include "grille.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

const int nb_type_tour = 1;
const int rayon_tour[nb_type_tour] = {5};
const int tps_recharge_tour[nb_type_tour] = {5};
const Color couleur_tour[nb_type_tour] = {RED};

class tour{
    point pos;
    int type;
    int rayon;
    int tps_recharge;
    int recharge; //recharge=0 -> prêt à tirer
    Color couleur;
public:
    tour();
    tour(int xi, int yi, int typei, grille g); //x,y -> coin supérieur gauche
    void affiche(grille g);
    void tire();
};
