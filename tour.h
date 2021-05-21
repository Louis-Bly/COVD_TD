#pragma once
#include <Imagine/Graphics.h>
using namespace Imagine;

const int nb_type_tour = 1;
const Color couleur_tour[nb_type_tour] = {RED};

class tour{
    int x,y;
    int type;
    int rayon;
    int tps_recharge;
    int recharge; //recharge=0 -> prêt à tirer
public:
    tour(int x, int y, int type); //x,y -> coin supérieur gauche
    void affiche();
    void tire();
};
