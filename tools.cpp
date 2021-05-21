#include "tools.h"

#include <iostream>
using namespace std;

#include <string>
using namespace std;

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
