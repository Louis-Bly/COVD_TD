#pragma once
#include "ennemi.h"

const int nb_type_projectiles = 1;
const int vitesses_projectiles[nb_type_projectiles] = {15};
const int taille_projectiles[nb_type_projectiles] = {3};
const int degats_projectiles[nb_type_projectiles] = {1};
const Color couleur_projectiles[nb_type_projectiles] = {GREEN};

class projectile{
    point pos;
    vect vit;
    int taille;
    int degats;
    Color couleur;
public:
    projectile(int xi, int yi, int typei, vect diri);
    void affiche();
    void efface();
    void deplace();
    int getdegats(){return degats;};
};
