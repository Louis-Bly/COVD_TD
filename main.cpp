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
#include "menu_principal.h"

#include <string>
using namespace std;

ennemi* liste_ennemis;
tour* liste_tours;
projectile* liste_projectiles;

void test()
{

    init_random();

    int buffer_tour=-1;
    const int largeur_fenetre = 1900;
    const int hauteur_fenetre = 1000;
    const int taille_marge = 160;
    const int taille_case = 75;
    interface Interface=interface(4,largeur_fenetre,hauteur_fenetre,taille_marge,120,200,70);

    point position_origine_b;
    position_origine_b.x=Interface.get_largeur()+100;
    position_origine_b.y=floor(taille_case/2);

    point position_origine_r;
    position_origine_r.x=Interface.get_largeur()+100;
    position_origine_r.y=floor(taille_case/2)+taille_case*3;

    point position_origine_a;
    position_origine_a.x=Interface.get_largeur()+400;
    position_origine_a.y=floor(taille_case/2)+taille_case*6;

    point position_origine_t;
    position_origine_t.x=Interface.get_largeur()+10;
    position_origine_t.y=floor(taille_case/2)+taille_case*9;

    liste_ennemis = new ennemi[4];
    grille g(largeur_fenetre,hauteur_fenetre-taille_marge,taille_case);
    liste_tours = new tour [g.get_nombre_case()]; //g.get_nombre_case après le merge
    liste_projectiles = new projectile [g.get_nombre_case()]; //g.get_nombre_case après le merge
    int indice_arrivee=0;
    point a = g.get_indices_xy(indice_arrivee);// On pourrait empecher le joueur de placer une tour sur la case d'arrivee ici, mais étant donné que l'on vérifie que les ennemis peuvent toujours rejoindre l'arrivée à chaque nouvelle tour, il est inutile de bloquer l'arrivee ici


    Interface.liste_test(position_origine_b,position_origine_r,position_origine_a,position_origine_t, liste_ennemis, g);



    openWindow(Interface.get_largeur(),Interface.get_hauteur());
    drawArrow(100,100,200,200,RED,50,50,0,8);
    click();
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

            //TEST
            int ar=0;
            int k=Interface.get_nb_ennemi();
            if ((liste_ennemis[i].get_case_actuelle().x==a.x)&&(liste_ennemis[i].get_case_actuelle().y==a.y))
            {
                liste_ennemis[i].Perte_vie(liste_ennemis[i].get_hp(), ar, i, k, liste_ennemis);
                Interface.set_nb_ennemi(k);
            }
            if (liste_ennemis[i].get_dans_le_cadre())
            {
                liste_ennemis[i].Chemin_ennemi.Calcul_plus_court_chemin(g.get_indices_xy(g.get_place(liste_ennemis[i].get_position())),g,a);
            }
            //TEST

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
        Interface.choisir_tour(buffer_tour,liste_tours, g, liste_ennemis, a);



        milliSleep(100);
    }
}

int main()
{
    const int largeur_fenetre = 1900;
    const int hauteur_fenetre = 1000;
    const int marge_cote = 400;
    int taille_tour=75;
    Menu M(largeur_fenetre, hauteur_fenetre, marge_cote, taille_tour);
    M.Menu_principal();
//    test();


    return 0;
}
