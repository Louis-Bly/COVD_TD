#include <Imagine/Graphics.h>
using namespace Imagine;

#include "ennemi.h"
#include "interface.h"
#include "chemin.h"

#include <string>
using namespace std;

int main()
{
    //TEST
    point position_origine_b;
    position_origine_b.x=1500;
    position_origine_b.y=200;

    point position_origine_r;
    position_origine_r.x=1500;
    position_origine_r.y=300;

    point position_origine_a;
    position_origine_a.x=1500;
    position_origine_a.y=400;

    point position_origine_t;
    position_origine_t.x=1500;
    position_origine_t.y=500;


    int d=30;
    int argent=0;
    int buffer_tour=-1;

    interface Interface=interface(4,1900,1000,150,120,200,70);

    //Interface.liste_ennemi[0]=ennemi_basique(position_origine_b);
    //Interface.liste_ennemi[1]=ennemi_rapide(position_origine_r);
    //Interface.liste_ennemi[2]=ennemi_ameliore(position_origine_a);
    //Interface.liste_ennemi[3]=ennemi_tank(position_origine_t);
    ennemi E_b=ennemi_basique(position_origine_b); //TEST



    openWindow(Interface.largeur,Interface.hauteur);
    Interface.Affiche_marge();
    Interface.Affiche_nb_ennemi_restant();
    Interface.Affiche_argent();
    for(int i=0;i<6;i++)
    {
        int j =i;
        Interface.Affiche_case_tour(j);
    }

    for (int i=0; i<Interface.nb_ennemi; i++)
    {
        //Interface.liste_ennemi[i].Affiche_ennemi();
        //Interface.liste_ennemi[i].Affiche_barre_vie();
        E_b.Affiche_barre_vie();
        E_b.Affiche_ennemi();

    }
    while (1>0)
    {
        for (int i=0; i<Interface.nb_ennemi; i++)
        {
            //Interface.liste_ennemi[i].Perte_vie(30,argent,nb);
            //Interface.liste_ennemi[i].Deplace();
            //E_b.Perte_vie(30,argent,0,Interface.nb_ennemi);
            E_b.Deplace();
            Interface.choisir_tour(buffer_tour);
        }
        milliSleep(100);
    }




    return 0;
}
