#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;


class vect{
    double x,y;
public:
    vect();
    vect(double xi,double yi);
    vect operator*(double k);
    int getx(){return x;};
    int gety(){return y;};
    void setx(double xd){x = xd;};
    void sety(double yd){y = yd;};
    vect normalise();
};

//On créé une structure point
struct point
{
    int x;
    int y;
    point operator+(vect depl);
    point operator-(point p2);
    double norm();
};

point Souris_clique_gauche();

const point dir[4] = {{1,0},{0,1},{-1,0},{0,-1}};
