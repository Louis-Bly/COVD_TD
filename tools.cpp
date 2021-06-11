#include "tools.h"

#include <iostream>
using namespace std;

#include <string>
using namespace std;


vect::vect(){
    x=0;
    y=0;
}

vect::vect(double xi,double yi){
    x=xi;
    y=yi;
}


vect vect::operator*(double k){
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


point point::operator-(point p2){
    point dif;
    dif.x = x-p2.x;
    dif.y = y-p2.y;
    return dif;
}


bool point::operator==(point p2){
    return(x==p2.x and y==p2.y);
}

double point::norm(){
    return sqrt(pow(x,2)+pow(y,2));
}


point Souris_clique_gauche() {
    point p;
    Event e;
    p.x = -1;
    p.y = -1;
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

void init_random()
{
    srand((unsigned int)time(0));
    rand();
}
