#include "tour.h"


tour::tour(){

}

tour::tour(int xi, int yi, int typei, grille g){  //x,y -> coin supérieur gauche
    point pi;
    pi.x = xi;
    pi.y = yi;
    pos = g.get_pos(g.get_place(pi)); //On replace la position en haut à gauche de la case
    g.ajout_tour(g.get_place(pi));    //On actualise la position dans les listes pour calculer l'itinéraire des ennemis
    type = typei;
    rayon = rayon_tour[typei];
    tps_recharge = tps_recharge_tour[typei];
    recharge = 0;
    couleur = couleur_tour[typei];
}

void tour::affiche(grille g){
    fillRect(pos.x,pos.y,g.get_taille_case(),g.get_taille_case(),couleur);
}

void tour::efface(grille g){
    fillRect(pos.x,pos.y,g.get_taille_case(),g.get_taille_case(),WHITE);
}

bool tour::tire(int nb_ennemis, int &nb_proj, int taille_case, ennemi liste_ennemis[], projectile liste_projectiles[]){
    if(recharge==0){ //Si la tour est prête à tirer
        ennemi cible;
        if(trouve_cible(cible, liste_ennemis, nb_ennemis)){ //Si on trouve un ennemi sur lequel tirer
            vect dirtir(cible.get_position().x-(pos.x+taille_case/2),cible.get_position().y-(pos.y+taille_case/2));
            dirtir = dirtir.normalise();                                                //On crée un vecteur normalisé pointangt vers l'ennemi
            projectile proj(pos.x+taille_case/2,pos.y+taille_case/2,rayon,type,dirtir);
            liste_projectiles[nb_proj] = proj;                                          //On crée un projectile lancé vers cet ennemi
            recharge = tps_recharge;
            nb_proj ++;
            return true;
        }
    }
    else{
        recharge--;
    }
    return false;
}

bool tour::trouve_cible(ennemi &cible, ennemi liste_ennemis[], int nb_ennemis){
    bool trouve = false;
    double mindist = (liste_ennemis[0].get_position()-pos).norm() + 1;
    for(int i=0; i<nb_ennemis; i++){
        double dist = (liste_ennemis[i].get_position()-pos).norm(); //La fonction trouve l'ennemi le plus proche de la tour
        if(dist < rayon and dist < mindist){
            mindist = dist;
            trouve = true;
            cible = liste_ennemis[i];
        }
    }
    return trouve;
}
