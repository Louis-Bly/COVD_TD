#define _USE_MATH_DEFINES
#include <cmath>
#include "fastMarching.h"
#include "priorite.h"
#include <algorithm>

const int voisin[4][2] = { {-1,0}, {+1,0}, {0,-1}, {0,+1} };

// Met dans dx et dy les plus petites valeurs des voisins du pixel (x,y).
void minVoisins(const Image<float>& D, int x, int y, float& dx, float& dy)
{
    const int w=D.width();
    const int h=D.height();
    if (x==0)
    {
        dx=D(1,y);
    }
    else if (x==w-1)
    {
        dx=D(w-2,y);
    }
    else
    {
        dx=min(D(x-1,y),D(x+1,y));
    }

    if (y==0)
    {
        dy=D(x,1);
    }
    else if (y==h-1)
    {
        dy=D(x,h-2);
    }
    else
    {
        dy=min(D(x,y-1),D(x,y+1));
    }
}

// Met a jour et renvoie la distance D(x,y) en fonction des voisins.
float calcDistance(Image<float>& D, const Image<float>& W, int x, int y) {
    float d1,d2;
    minVoisins(D,x,y,d2,d1);
    if (2*pow(W(x,y),2)-pow(d1-d2,2)<0) //On a d1 ou d2 qui n'est pas fini
    {
        D(x,y)=min(d1,d2)+W(x,y);
    }
    else // d1 et d2 sont finis
    {
        D(x,y)=(d1+d2+std::sqrt(2*W(x,y)*W(x,y)-(d1-d2)*(d1-d2)))/2;
    }
    float a=D(x,y);
    return D(x,y);
}

// Fast Marching: carte de distance a partir des points de niv0, qui sont a
// distance 0 par definition.
Image<float> fastMarching(const Image<float>& W, const vector<PointDist>& niv0){
    const int w=W.width(), h=W.height();

    // Initialisation
    Image<float> D(w,h); D.fill(INF);
    Image<bool>  E(w,h); E.fill(false);
    for (int i=0; i<w;i++)
    {
        for (int j=0; j<h; j++)
        {
            if (W(i,j)==INF) //Les obstacles sont considérés comme deja visitee
            {
                E(i,j)=true;
            }
        }
    }
    FilePriorite F;
    int n =niv0.size();
    for (int i=0; i<n;i++)
    {
        F.push(niv0[i]);
        int x=niv0[i].i;
        int y=niv0[i].j;
        D(x,y)=0;
        E(x,y)=true;
    }
    while (F.empty()==false)
    {
        PointDist p=F.pop();
        for (int a=0;a<4;a++)
        {
            int i_v=p.i+voisin[a][0];
            int j_v=p.j+voisin[a][1];
            if ((i_v>=0) && (i_v<w) && (j_v>=0) && (j_v<h) && (W(i_v,j_v)>0) && (E(i_v,j_v)==false))
            {
                float d=calcDistance(D,W,i_v,j_v);
                E(i_v,j_v)=true;
                PointDist q(i_v,j_v,-d);
                F.push(q);
            }
        }
    }
    return D;
}

// Affiche en couleur l'image des distances.
// bleu=0, rouge=maximum, vert=infini
void affiche(const Image<float>& I) {
    Image<float> D=I.clone();
    for(int i=0; i<D.height(); i++)
        for(int j=0; j<D.width(); j++)
            if(D(j,i)==INF)
                D(j,i)=-1.0f;
    float M = *max_element(D.begin(), D.end());
    M = max(1.0f,M);
    Image<Color> B(D.width(), D.height());
    for(int i=0; i<D.height(); i++)
        for(int j=0; j<D.width(); j++)
        {
            if(D(j,i)>=0)
            {
                float angle=M_PI/2*D(j,i)/M;
                B(j,i) = Color(byte(255*sin(angle)), 0, byte(255*cos(angle)));
            }
            else B(j,i) = GREEN;
        }
    display(B);
}
