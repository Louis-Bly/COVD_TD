#include <Imagine/Graphics.h>
using namespace Imagine;

#include <iostream>
using namespace std;

#include "ennemi.h"
#include "interface.h"
#include "chemin.h"
#include "grille.h"
#include "tour.h"
#include "projectile.h"

#include <string>
using namespace std;

ennemi* liste_ennemis;
tour* liste_tours;
projectile* liste_projectiles;

void testAstar()
{
    int buffer_tour=-1;
    const int largeur_fenetre = 1900;
    const int hauteur_fenetre = 1000;
    const int taille_marge = 160;
    interface Interface=interface(4,largeur_fenetre,hauteur_fenetre,taille_marge,120,200,70);
    liste_ennemis = new ennemi[4];

    openWindow(Interface.get_largeur(),Interface.get_hauteur());
    Interface.Affiche_marge();
    Interface.Affiche_nb_ennemi_restant();
    Interface.Affiche_argent();
    for(int i=0;i<6;i++)
    {
        int j =i;
        Interface.Affiche_case_tour(j);
    }
    int taille_case = 75;
    grille g(largeur_fenetre,hauteur_fenetre-taille_marge,taille_case);
    liste_tours = new tour [1000]; //g.get_nombre_case() après le merge
    g.affiche();


    int arrivee_i=38;
//    int depart_i=124;

    for (int i=0; i<27;i++)
    {
        int tour=6*i;
        g.set_libre_ennemi(tour,false);
        point t=g.get_indices_xy(tour);
        fillRect(t.x*g.get_taille_case(),t.y*g.get_taille_case(),g.get_taille_case(),g.get_taille_case(), BLACK);
    }



    point a= g.get_indices_xy(arrivee_i);
    fillRect(a.x*g.get_taille_case(),a.y*g.get_taille_case(),g.get_taille_case(),g.get_taille_case(), BLUE);

    //TEST

    point position_origine_b;
    position_origine_b.x=Interface.get_largeur()+5*3;
    position_origine_b.y=200;

    point position_origine_r;
    position_origine_r.x=Interface.get_largeur()+15*3;
    position_origine_r.y=400;

    point position_origine_a;
    position_origine_a.x=Interface.get_largeur()+6*3;
    position_origine_a.y=600;

    point position_origine_t;
    position_origine_t.x=Interface.get_largeur()+2*3;
    position_origine_t.y=800;

    ennemi E=ennemi_basique(position_origine_b,g);
    ennemi E2=ennemi_rapide(position_origine_r,g);
    Interface.liste_test(position_origine_b,position_origine_r,position_origine_a,position_origine_t, liste_ennemis, g);
    for (int i=0; i<Interface.get_nb_ennemi(); i++)
    {
        liste_ennemis[i].Affiche_ennemi();
        liste_ennemis[i].Affiche_barre_vie();

    }


    liste_tours = new tour [1000]; //g.get_nombre_case après le merge
    while (Interface.get_nb_ennemi()>0)
    {
        g.affiche();
        for (int i=0; i<Interface.get_nb_ennemi(); i++)
        {
            int ennemis_act = Interface.get_nb_ennemi();
            int argent_act = Interface.get_Argent();
            liste_ennemis[i].Perte_vie(0,argent_act,i,ennemis_act,liste_ennemis);
            Interface.set_Argent(argent_act);
            Interface.set_nb_ennemi(ennemis_act);
            Interface.Affiche_argent();
            for (int n=0;n<6;n++)
            {
                Interface.dessine_argent_suffisant(n,n);
            }
            liste_ennemis[i].Deplace(g,a);
            Interface.choisir_tour(buffer_tour, liste_tours, g);
        }
        milliSleep(200);
    }
//    while(true)
//    {
//        E.Deplace(g,a);
//        E2.Deplace(g,a);
//        milliSleep(200);
//    }



//    point dep=g.get_indices_xy(depart_i);
//    chemin C=chemin(g);
//    fillRect(a.x*g.get_taille_case(),a.y*g.get_taille_case(),g.get_taille_case(),g.get_taille_case(), BLUE);
//    fillRect(dep.x*g.get_taille_case(),dep.y*g.get_taille_case(),g.get_taille_case(),g.get_taille_case(), GREEN);
//    bool T=C.Calcul_plus_court_chemin(dep,g,a);
//    if (T)
//    {

//        for (int i=C.get_taille_chemin()-1; i>=0;i--)
//        {
//            int indice=C.get_chemin_de_ennemi(i);
//            point pi= g.get_indices_xy(indice);
//            fillRect(pi.x*g.get_taille_case(),pi.y*g.get_taille_case(),g.get_taille_case(),g.get_taille_case(), RED);
//            click();
//        }
//    }

}

void test()
{


    int buffer_tour=-1;
    const int largeur_fenetre = 1900;
    const int hauteur_fenetre = 1000;
    const int taille_marge = 160;
    const int taille_case = 75;
    interface Interface=interface(4,largeur_fenetre,hauteur_fenetre,taille_marge,120,200,70);

    point position_origine_b;
    position_origine_b.x=Interface.get_largeur()+1000;
    position_origine_b.y=200;

    point position_origine_r;
    position_origine_r.x=Interface.get_largeur()+1000;
    position_origine_r.y=400;

    point position_origine_a;
    position_origine_a.x=Interface.get_largeur()+1000;
    position_origine_a.y=600;

    point position_origine_t;
    position_origine_t.x=Interface.get_largeur()+1000;
    position_origine_t.y=800;

    liste_ennemis = new ennemi[4];
    grille g(largeur_fenetre,hauteur_fenetre-taille_marge,taille_case);
    liste_tours = new tour [g.get_nombre_case()]; //g.get_nombre_case après le merge
    liste_projectiles = new projectile [1000]; //g.get_nombre_case après le merge
    point a = g.get_indices_xy(0);

    Interface.liste_test(position_origine_b,position_origine_r,position_origine_a,position_origine_t, liste_ennemis, g);



    openWindow(Interface.get_largeur(),Interface.get_hauteur());
    Interface.Affiche_marge();
    Interface.Affiche_nb_ennemi_restant();
    Interface.Affiche_argent();
    for(int i=0;i<6;i++)
    {
        int j =i;
        Interface.Affiche_case_tour(j);
    }

    for (int i=0; i<Interface.get_nb_ennemi(); i++)
    {
        liste_ennemis[i].Affiche_ennemi();
        liste_ennemis[i].Affiche_barre_vie();

    }
    while (Interface.get_nb_ennemi()>0)
    {
        for(int i=0; i<Interface.get_nb_proj();i++){
            liste_projectiles[i].efface();
        }
        g.affiche();
        for (int i=0; i<Interface.get_nb_ennemi(); i++)
        {
            Interface.Affiche_argent();
            for(int i=0; i<Interface.get_nb_tour(); i++){
                liste_tours[i].affiche(g);
                int nbproj = Interface.get_nb_proj();
                liste_tours[i].tire(Interface.get_nb_ennemi(),nbproj,g.get_taille_case(),liste_ennemis,liste_projectiles);
                Interface.set_nb_proj(nbproj);
            }
            for (int n=0;n<6;n++)
            {
                Interface.dessine_argent_suffisant(n,n);
            }
            liste_ennemis[i].Deplace(g,a);
        }
        for(int i=0; i<Interface.get_nb_proj();i++){
            liste_projectiles[i].deplace();
            int nb_proj = Interface.get_nb_proj();
            int nb_ennemi = Interface.get_nb_ennemi();
            int argent_act = Interface.get_Argent();
            liste_projectiles[i].collision(i, liste_projectiles, liste_ennemis, nb_proj, nb_ennemi, largeur_fenetre, hauteur_fenetre-taille_marge-10, argent_act);
            Interface.set_nb_proj(nb_proj);
            Interface.set_nb_ennemi(nb_ennemi);
            Interface.set_Argent(argent_act);
        }
        Interface.choisir_tour(buffer_tour,liste_tours, g);
        milliSleep(100);
    }
}

int main()
{
    test();

    return 0;
}
