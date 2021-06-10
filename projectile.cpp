#include "projectile.h"


projectile::projectile(){

}

projectile::projectile(int xi, int yi, int dist_maxi, int typei, vect diri){
    pos.x = xi;
    pos.y = yi;
    orig.x = xi;
    orig.y = yi;
    vit = diri*vitesses_projectiles[typei];
    dist_max = dist_maxi;
    type = typei;
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
    pos = pos + vit;
    affiche();
}

void projectile::collision(int& i, projectile liste_projectiles[], ennemi liste_ennemis[], int& nb_proj, int& nb_ennemi, int maxx, int maxy, int& argent){
    bool out = pos.x<0 or pos.y < 0 or pos.x>maxx or pos.y>maxy;
    bool far = (pos-orig).norm() > dist_max;
    bool hit = false;
    for(int j=0;j<nb_ennemi;j++){
        if((pos-liste_ennemis[j].get_position()).norm()-taille/2 < liste_ennemis[j].get_rayon()){
            liste_ennemis[j].Perte_vie(degats, argent, j, nb_ennemi, liste_ennemis);
            if(type == 4){
                drawCircle(pos.x,pos.y,taille*4,couleur);
                for(int k=0;k<nb_ennemi;k++){
                    if((pos-liste_ennemis[k].get_position()).norm() < taille*4){
                        liste_ennemis[k].Perte_vie(degats, argent, j, nb_ennemi, liste_ennemis);
                    }
                }
                milliSleep(70);
                drawCircle(pos.x,pos.y,taille*4,WHITE);
            }
            hit = true;
        }
    }
    bool destroy;
    if(type == 3) destroy = out;
    else destroy = out or hit or far;
    if(destroy){
        vit = vit*0;
        efface();
        nb_proj --;
        liste_projectiles[i] = liste_projectiles[nb_proj];
        i--;
    }
}
