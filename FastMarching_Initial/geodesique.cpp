// Author: 

#include "fastMarching.h"
#include <iostream>

typedef FVector<float,2> FloatPoint2; // point avec coordonnees float

const float EPSILON=10.0f; // Spatial length parameter
const float TAU=0.8f; // Increment dans la direction opposee au gradient
const size_t MAX_LENGTH=1000; // Max length of a geodesic

// Remplis l'image des poids, fonction croissante de la distance en couleur
// du point courant a I(p).
Image<float> remplisPoids(const Image<Color>& I, const IntPoint2& p)
{
    int w =I.width(); int h=I.height();
    Image<float> W(w, h);
    for (int i=0;i<w;i++)
    {
        for (int j=0;j<h;j++)
        {
            W(i,j)=EPSILON + abs(float(I(i,j))-float(I(p[0],p[1])))/3;

            if ((j==0)||(i==0)||(i==w-1)||(j==h-1))
            {
                W(i,j)=INF;
            }
        }
    }
    return W;
}

IntPoint2 arrondi(const FloatPoint2& p) {
    return IntPoint2((int)(p[0]+0.5f), (int)(p[1]+0.5f));
}

// Calcule la geodesique de p1 a p2.
vector<FloatPoint2> geodesique(const Image<float>& D, FloatPoint2 p1, FloatPoint2 p2)
{
    vector<FloatPoint2> v;
    v.push_back(p2);
    FloatPoint2 q;
    q=p2;
    while (((sqrt((q[0]-p1[0])*(q[0]-p1[0])+(q[1]-p1[1])*(q[1]-p1[1])))>1) &&(v.size()<MAX_LENGTH))
    {
        FloatPoint2 grad;
        grad[0]=D(q[0]+1,q[1])-D(q[0]-1,q[1]);
        grad[1]=D(q[0],q[1]+1)-D(q[0],q[1]-1);
        float g= sqrt(grad[0]*grad[0]+grad[1]*grad[1]);
        q[0]=q[0]-TAU*grad[0]/g;
        q[1]=q[1]-TAU*grad[1]/g;
        v.push_back(q);
        if (v.size()==MAX_LENGTH)
        {
            cout<<"Taille limite dépassée"<<endl;
        }
    }
    v.push_back(p1);
    return v;
}

int main() {
    Image<Color> I;
    Image<float> W;
    if(! load(I, argc>1? argv[1]: srcPath("map.png"))) {
        std::cout << "Echec de lecture d'image" << std::endl;
        return 1;
    }
    openWindow(I.width(), I.height());
    display(I);

    cout << "Cliquez les points de depart et d'arrivee" << endl;
    IntPoint2 p1, p2;
    while(getMouse(p1)==1) {
        display(I); //Image original
        W=remplisPoids(I,p1);

        fillCircle(p1,3,RED); //Point de départ en rouge
        getMouse(p2);
        fillCircle(p2,3,GREEN); //Point d'arrivée en vert
        click();


        std::vector<PointDist> v;
        PointDist P(p1[0],p1[1],0);
        v.push_back((P));
        Image<float> D = fastMarching(W, v);
        affiche(W); //image de cout par rapport au point de départ
        click();
        vector<FloatPoint2> a=geodesique(D,p1,p2);
        affiche(D); // image de distance par rapport au point de départ
        click();

        if (a.size()!=MAX_LENGTH)
        {
            // On affiche à nouveau l'image de départ et les points de départ et d'arrivée
            display(I);
            fillCircle(p1,3,RED);
            fillCircle(p2,3,GREEN);
            FloatPoint2 p_prec=a[a.size()-1];
            for (int i=a.size()-2;i>=0;i--)
            {
                FloatPoint2 p_nouv=a[i];
                drawLine(arrondi(p_nouv),arrondi(p_prec),BLUE); //géodésique tracer en bleu du point rouge au point vert
                p_prec=p_nouv;
            }
        }
    }
    display(I);
    // Pour quitter le programme, il faut faire autre chose qu'un clique gauche au moment où l'on choisi le point de départ (rouge)
    endGraphics();
    return 0;
}
