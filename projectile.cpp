#include "projectile.h"


projectile::projectile(int xi, int yi, int typei, vect diri){
    pos.x = xi;
    pos.y = yi;
    vit = diri*vitesses_projectiles[typei];
    taille = taille_projectiles[typei];
    degats = degats_projectiles[typei];
    couleur = couleur_projectiles[typei];
}


void projectile::affiche(){
    fillRect(pos.x,pos.y,taille,taille,couleur);
}

void projectile::efface(){
    fillRect(pos.x,pos.y,taille,taille,WHITE);
}

void projectile::deplace(){
    this->efface();
    pos = pos + vit;
    this->affiche();
}
