#pragma once
#include "ennemi.h"

const int nb_type_projectiles = 5;
const int vitesses_projectiles[nb_type_projectiles] = {0,20,20,30,15};
const int taille_projectiles[nb_type_projectiles] = {10,10,10,15,20};
const int degats_projectiles[nb_type_projectiles] = {0,10,50,20,30};
const Color couleur_projectiles[nb_type_projectiles] = {ORANGE,GREEN,MAGENTA,CYAN,RED};

class projectile{
    point pos;
    point orig;
    vect vit;
    int dist_max;
    int type;
    int taille;
    int degats;
    Color couleur;
public:
    projectile();
    projectile(int xi, int yi, int dist_maxi, int typei, vect diri);
    void affiche();
    void efface();
    void deplace();
    int getdegats(){return degats;};
    void collision(int &i, projectile liste_projectiles[], ennemi liste_ennemis[], int &nb_proj, int &nb_ennemi, int maxx, int maxy, int &argent);
};
