#include "projectile.h"


projectile::projectile(){

}

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
    efface();
    pos = pos + vit;
    affiche();
}

void projectile::collision(int& i, projectile liste_projectiles[], ennemi liste_ennemis[], int& nb_proj, int& nb_ennemi, int maxx, int maxy, int& argent){
    bool out = pos.x<0 or pos.y < 0 or pos.x>maxx or pos.y>maxy;
    bool hit = false;
    for(int j=0;j<nb_ennemi;j++){
        if((pos-liste_ennemis[j].get_position()).norm() < liste_ennemis[j].get_rayon()){
            liste_ennemis[j].Perte_vie(degats, argent, j, nb_ennemi, liste_ennemis);
            hit = true;
        }
    }
    if(out or hit){
        vit = vit*0;
        efface();
        liste_projectiles[i] = liste_projectiles[nb_proj];
        nb_proj --;
        i--;
    }
}
