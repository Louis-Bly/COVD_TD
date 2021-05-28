#include "tools.h"

#include <iostream>
using namespace std;

#include <string>
using namespace std;


vect::vect(){
    x=0;
    y=0;
}

vect::vect(int xi,int yi){
    x=xi;
    y=yi;
}


vect vect::operator*(int k){
    vect prod(k*x,k*y);
    return prod;
}


vect vect::normalise(){
    float coeff = sqrt(x*x+y*y);
    vect norm(x/coeff,y/coeff);
    return norm;
}


point point::operator+(vect depl){
    point sum;
    sum.x = x+depl.getx();
    sum.y = y+depl.gety();
    return sum;
}


point Souris_clique_gauche() {
    point p;
    Event e;
    do {
        getEvent(0,e);
        if (e.type==EVT_BUT_ON)
        {
            p.x=e.pix.x();
            p.y=e.pix.y();
            return p;
        }
    } while (e.type!=EVT_NONE);
    return p;
}
