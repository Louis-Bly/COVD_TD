#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;


class vect{
    int x,y;
public:
    vect();
    vect(int xi,int yi);
    vect operator*(int k);
    int getx(){return x;};
    int gety(){return y;};
    void setx(int xd){x = xd;};
    void sety(int yd){y = yd;};
    vect normalise();
};

//On créé une structure point
struct point
{
    int x;
    int y;
    point operator+(vect depl);
};

point Souris_clique_gauche();

const point dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};
