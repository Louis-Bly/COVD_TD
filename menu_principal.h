#pragma once
#include "ennemi.h"
#include "interface.h"
#include "chemin.h"
#include "grille.h"
#include "tour.h"
#include "projectile.h"
#include <string>
using namespace std;


class Menu
{
    int largeur;
    int hauteur;
    int ecart_cote;
    Color ecriture;
    Color remplissage;
    Color titre;
    string nom_du_jeu;
    string ecran_actif;
    int taille_tour;




public:

    Menu();
    Menu(int l, int h, int e, int t_tour);

    void Menu_principal();

    void draw_boutons_ecran_acceuil();
    void draw_boutons_ecran_jouer();
    void draw_boutons_ecran_info();

    void affichage();

    void efface_ecran();

    void changement_de_page();



    void regle();

    void Info_ennemi();

    void Info_tour();

};
