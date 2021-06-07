#pragma once
#include "ennemi.h"

const int nb_type_projectiles = 1;
const int vitesses_projectiles[nb_type_projectiles] = {20};
const int taille_projectiles[nb_type_projectiles] = {10};
const int degats_projectiles[nb_type_projectiles] = {20};
const Color couleur_projectiles[nb_type_projectiles] = {GREEN};

class projectile{
    point pos;
    vect vit;
    int taille;
    int degats;
    Color couleur;
public:
    projectile();
    projectile(int xi, int yi, int typei, vect diri);
    void affiche();
    void efface();
    void deplace();
    int getdegats(){return degats;};
    void collision(int &i, projectile liste_projectiles[], ennemi liste_ennemis[], int &nb_proj, int &nb_ennemi, int maxx, int maxy, int &argent);
};
