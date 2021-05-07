// Author: 

#include "fastMarching.h"
#include <iostream>

const int w=512, h=512;
const float TOL=0.1f; // Seuil de tolerance d'imprecision numerique

// Selection a la souris d'un rectangle.
bool selectionRect(int& x1, int& y1, int& x2, int& y2, const Image<Color>& I) {
    Event e;
    x1=x2=y1=y2=-1;
    do {
        getEvent(-1, e);
        if(e.type==EVT_BUT_ON) {
            x1 = x2 = e.pix[0];
            y1 = y2 = e.pix[1];
            if(e.button==3)
                return false;
        }
        if(e.type==EVT_MOTION) {
            if(x1<0) continue;
            x2 = e.pix[0];
            y2 = e.pix[1];
            display(I);
            fillRect(std::min(x1,x2), std::min(y1,y2), abs(x1-x2), abs(y1-y2),
                     RED);
        }
    } while(e.type!=EVT_BUT_OFF || abs(x1-x2)<5 || abs(y1-y2)<5);
    if(x1>x2) std::swap(x1,x2);
    if(y1>y2) std::swap(y1,y2);
    return true;
}

int main() {
    openWindow(w, h);
    Image<Color> I(w,h);
    I.fill(WHITE);
    int x1,y1,x2,y2;

    cout << "Dessinez des rectangles (il faut faire un clic gauche et maintenir la touche enfoncee pour tracer le rectangle), clic droit pour terminer" << endl;
    while (selectionRect(x1,y1,x2,y2,I)!=false)
    {
        fillRect(x1,y1,x2-x1,y2-y1,RED);
        for (int i=x1; i<x2;i++)
        {
            for (int j=y1; j<y2; j++)
            {
                I(i,j)=RED;
            }
        }
    }

    cout << "Cliquez la position de la source lumineuse" << endl;
    vector<PointDist> v;
    int x=w; int y=h;
    while ((x<0)||(x>=w)||(y<0)||(y>=h)||(I(x,y)==RED)) //On change de source tant que le point est sur une zone rouge ou hors de l'image
    {
        getMouse(x,y);
        fillCircle(x,y,2,YELLOW);
    }
    v.push_back(PointDist(x,y,0));


    // Remplissage des cartes de cout avec et sans obstacles
    Image<float> Wavec(w,h), Wsans(w,h);
    Wavec.fill(1.0f); Wsans.fill(1.0f);
    for (int i=0; i<w;i++)
    {
        for (int j=0; j<h; j++)
        {
            if (I(i,j)==RED)
            {
                Wavec(i,j)=INF;
            }
        }
    }


    cout << "Calcul" << endl;
    Image<float> Davec = fastMarching(Wavec, v);
    Image<float> Dsans = fastMarching(Wsans, v);
    for (int i=0; i<w;i++)
    {
        for (int j=0; j<h; j++)
        {
            if ((Davec(i,j)>Dsans(i,j)+TOL) && (I(i,j)!=RED))
            {
                I(i,j)=BLUE;
            }
        }
    }
    display(I);
    fillCircle(x,y,2,YELLOW);
    Window W1 = openWindow(w,h);
    setActiveWindow(W1);
    affiche(Davec);
    fillCircle(x,y,2,YELLOW);
    Window W2 = openWindow(w,h);
    setActiveWindow(W2);
    affiche(Dsans);
    fillCircle(x,y,2,YELLOW);

    endGraphics();
    return 0;
}
