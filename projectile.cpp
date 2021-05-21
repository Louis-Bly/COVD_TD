#include "projectile.h"


projectile::projectile(int x, int y, int type, int dir){

}


void projectile::deplace(){

    x += vx;
    y += vy;
}
