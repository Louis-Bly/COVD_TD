#pragma once


#include <Imagine/Graphics.h>
using namespace Imagine;

#include "ennemi.h"
#include "chemin.h"
#include "tools.h"

class interface
{
    int largeur;
    int hauteur;
    Color couleur_arriere_plan;
    int nb_ennemi_initial;
    int taille_marge; //La marge contient l'interface pour poser des tours

    int hauteur_case_tour;
    int largeur_case_tour;
    int ecart_case_tour;

public:

    int Argent;
    int nb_ennemi;
    ennemi* liste_ennemi;


    //Constructeur
    interface();
    interface(int nb, int hauteur, int largeur, int hauteur_marge, int h_tour, int l_tour, int e_case_tour);

    //Fonctions get:

    int get_largeur(){return largeur;};
    int get_hauteur(){return hauteur;};
    int get_nb_ennemi(){return nb_ennemi;};

    //Fonctions d'affichages

    void Affiche_nb_ennemi_restant();
    void Affiche_argent();
    void Affiche_marge();
    void Affiche_case_tour(int &indice);

    //Utilisations des cases pour placer les tours
    void choisir_tour(int &n);
    int case_selectionnees(int x, int y);
    bool choisir_position_tour(int &n); //Prendra aussi les tours en paramètres

    bool confirmer_placement();

    void dessine_argent_suffisant(int cout, int n);

    //TEST
    void liste_test(point position_origine_b,point position_origine_r,point position_origine_a,point position_origine_t);


};
