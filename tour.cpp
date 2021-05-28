#include "tour.h"


tour::tour(int xi, int yi, int typei){  //x,y -> coin supérieur gauche
    pos.x = xi;
    pos.y = yi;
    type = typei;
    rayon = rayon_tour[typei];
    tps_recharge = tps_recharge_tour[typei];
    recharge = 0;
    couleur = couleur_tour[typei];
}

void tour::affiche(){
    fillRect(pos.x,pos.y,rayon,rayon,couleur);
}

void tour::tire(){

}
