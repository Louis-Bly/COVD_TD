#pragma once
#include "ennemi.h"

const int nb_type_projectiles = 1;
const int vitesses_projectiles[nb_type_projectiles] = {15};

class projectile{
    int x,y;
    int vx,vy;
    int degats;
public:
    projectile(int x, int y, int type, int dir);
    void deplace();
    int getdegats(){return degats;};
};

void test(projectile proj, ennemi* ennemis);
