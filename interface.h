#pragma once


#include <Imagine/Graphics.h>
using namespace Imagine;

#include "ennemi.h"
#include "tour.h"
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

    int Argent;
    int nb_ennemi;
    int nb_tour;
    int nb_proj;

public:


    //Constructeur
    interface();
    interface(int nb, int hauteur, int largeur, int hauteur_marge, int h_tour, int l_tour, int e_case_tour);

    //Fonctions get:

    int get_largeur(){return largeur;};
    int get_hauteur(){return hauteur;};
    int get_taille_marge(){return taille_marge;};
    int get_Argent(){return Argent;};
    int get_nb_ennemi(){return nb_ennemi;};
    int get_nb_tour(){return nb_tour;};
    int get_nb_proj(){return nb_proj;};

    //Fonctions set:

    void set_Argent(int i){Argent = i;};
    void set_nb_ennemi(int i){nb_ennemi = i;};
    void set_nb_tours(int i){nb_tour = i;};
    void set_nb_proj(int i){nb_proj = i;};

    //Fonctions d'affichages

    void Affiche_nb_ennemi_restant();
    void Affiche_argent();
    void Affiche_marge();
    void Affiche_case_tour(int &indice);

    //Utilisations des cases pour placer les tours
    void choisir_tour(int &n, tour liste_tours[], grille g);
    int case_selectionnees(int x, int y);
    bool choisir_position_tour(int &n, tour liste_tours[], grille g); //Prendra aussi les tours en paramètres

    bool confirmer_placement();

    void dessine_argent_suffisant(int cout, int n);

    //TEST
    void liste_test(point position_origine_b, point position_origine_r, point position_origine_a, point position_origine_t, ennemi liste_ennemis[]);


};
