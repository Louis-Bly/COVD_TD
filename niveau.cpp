#include "niveau.h"

ennemi* liste_ennemis;
tour* liste_tours;
projectile* liste_projectiles;

void tutoriel(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{

    init_random();
    int nb_ennemi_basique=1;
    int nb_ennemi_ameliore=1;
    int nb_ennemi_rapide=1;
    int nb_ennemi_tank=1;
    bool tutoriel=true; //Tous les ennemis apparaissent en même temps dans le tutoriel
    int indice_arrivee=0;
    int ecart=100; //Pas utile dans le tutoriel, utile seulement dans les autres niveaux
    int argent=1000;
    niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart, argent, indice_arrivee, tutoriel);

}

void niveau1(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    int nb_ennemi_basique=50;
    int nb_ennemi_ameliore=20;
    int nb_ennemi_rapide=20;
    int nb_ennemi_tank=10;
    int ecart_moyen=25;
    int argent=100;
    int indice_arrivee=0;
    niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

void niveau2(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    int nb_ennemi_basique=30;
    int nb_ennemi_ameliore=60;
    int nb_ennemi_rapide=5;
    int nb_ennemi_tank=20;
    int ecart_moyen=20;
    int argent=100;
    int indice_arrivee=0;
    niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

void niveau3(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    int nb_ennemi_basique=100;
    int nb_ennemi_ameliore=10;
    int nb_ennemi_rapide=60;
    int nb_ennemi_tank=10;
    int ecart_moyen=30;
    int argent=100;
    int indice_arrivee=0;
    niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

void niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case, int nb_basique, int nb_ameliore, int nb_rapide, int nb_tank, int ecart_moyen, int argent_initial, int indice_arrivee, bool tutoriel)
{

    int buffer_tour=-1;
    const int taille_marge = 160;
    int nb_ennemis=nb_ameliore+nb_basique+nb_rapide+nb_tank;
    interface Interface=interface(nb_ennemis,largeur_fenetre,hauteur_fenetre,taille_marge,120,200,70, argent_initial);

    liste_ennemis = new ennemi[nb_ennemis];
    grille g(largeur_fenetre,hauteur_fenetre-taille_marge,taille_case);

    liste_tours = new tour [g.get_nombre_case()]; //g.get_nombre_case après le merge
    liste_projectiles = new projectile [g.get_nombre_case()]; //g.get_nombre_case après le merge
    point a = g.get_indices_xy(indice_arrivee); // Définition du point arrivée (ligne/colonne)

    //Définition des positions de départ des ennemis

    point position_origine_b;
    point position_origine_r;
    point position_origine_a;
    point position_origine_t;

    for (int i=0; i<nb_basique;i++)
    {
        if(tutoriel)
        {
            position_origine_b.x=Interface.get_largeur()+500;
            position_origine_b.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_b.x=Interface.get_largeur()+c*5;
            position_origine_b.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_basique(position_origine_b, g);
    }
    for (int i=nb_basique; i<nb_basique+nb_ameliore;i++)
    {
        if(tutoriel)
        {
            position_origine_a.x=Interface.get_largeur()+100;
            position_origine_a.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_a.x=Interface.get_largeur()+c*6;
            position_origine_a.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_ameliore(position_origine_a, g);
    }
    for (int i=nb_basique+nb_ameliore; i<nb_basique+nb_ameliore+nb_rapide;i++)
    {
        if(tutoriel)
        {
            position_origine_r.x=Interface.get_largeur()+2500;
            position_origine_r.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_r.x=Interface.get_largeur()+c*15;
            position_origine_r.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_rapide(position_origine_r, g);
    }
    for (int i=nb_basique+nb_ameliore+nb_rapide; i<nb_ennemis;i++)
    {
        if(tutoriel)
        {
            position_origine_t.x=Interface.get_largeur()+400;
            position_origine_t.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_t.x=Interface.get_largeur()+c*2;
            position_origine_t.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_tank(position_origine_t, g);
    }

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
