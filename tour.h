#pragma once
#include "tools.h"
#include "grille.h"
#include "ennemi.h"
#include "projectile.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

const int nb_type_tour = 1;
const int rayon_tour[nb_type_tour] = {500};
const int tps_recharge_tour[nb_type_tour] = {10};
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
    bool tire(int nb_ennemis, int &nb_proj, int taille_case, ennemi liste_ennemis[], projectile liste_projectiles[]);
    bool trouve_cible(ennemi &cible, ennemi liste_ennemis[], int nb_ennemis);

};
