#include "tour.h"


tour::tour(int xi, int yi, int typei, grille g){  //x,y -> coin supérieur gauche
    point pi;
    pi.x = xi;
    pi.y = yi;
    pos = g.get_pos(g.get_place(pi));
    g.ajout_tour(g.get_place(pi));
    type = typei;
    rayon = rayon_tour[typei];
    tps_recharge = tps_recharge_tour[typei];
    recharge = 0;
    couleur = couleur_tour[typei];
}

void tour::affiche(grille g){
    fillRect(pos.x,pos.y,g.get_taille_case(),rayon,couleur);
}

void tour::tire(){

}
