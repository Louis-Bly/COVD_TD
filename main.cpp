#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include "ennemi.h"
#include "interface.h"
#include "chemin.h"

#include <string>
using namespace std;

void test()
{
    point position_origine_b;
    position_origine_b.x=1500;
    position_origine_b.y=200;

    point position_origine_r;
    position_origine_r.x=1500;
    position_origine_r.y=400;

    point position_origine_a;
    position_origine_a.x=1500;
    position_origine_a.y=600;

    point position_origine_t;
    position_origine_t.x=1500;
    position_origine_t.y=800;


    int buffer_tour=-1;

    interface Interface=interface(4,1900,1000,160,120,200,70);

    Interface.liste_test(position_origine_b,position_origine_r,position_origine_a,position_origine_t);



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
        Interface.liste_ennemi[i].Affiche_ennemi();
        Interface.liste_ennemi[i].Affiche_barre_vie();

    }
    while (Interface.nb_ennemi>0)
    {
        for (int i=0; i<Interface.nb_ennemi; i++)
        {
            if (Interface.liste_ennemi[i].Perte_vie(10,Interface.Argent,i,Interface.nb_ennemi,Interface.liste_ennemi))
            {
                Interface.Affiche_argent();
                for (int n=0;n<6;n++)
                {
                    Interface.dessine_argent_suffisant(n,n);
                }
            }
            Interface.liste_ennemi[i].Deplace();
            Interface.choisir_tour(buffer_tour);
        }
        milliSleep(200);
    }
}

int main()
{
    test();

    return 0;
}
