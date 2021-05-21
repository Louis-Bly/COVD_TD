#pragma once

#include "ennemi.h"
#include "chemin.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class interface
{
public:
    int largeur;
    int hauteur;
    int Argent;
    int nb_ennemi_initial;
    int nb_ennemi;
    int taille_marge; //La marge contient l'interface pour poser des tours

    int hauteur_case_tour;
    int largeur_case_tour;
    int ecart_case_tour;

    //ennemi* liste_ennemi;

    //Constructeur
    interface(int nb, int hauteur, int largeur, int hauteur_marge, int h_tour, int l_tour, int e_case_tour);


    //Fonctions d'affichages


    void Affiche_nb_ennemi_restant();
    void Affiche_argent();
    void Affiche_marge();
    void Affiche_case_tour(int indice);

    //Utilisations des cases pour placer les tours
    void choisir_tour();
    int case_selectionnees(int x, int y);
    void choisir_position_tour(int n); //Prendra aussi les tours en paramètres

    bool confirmer_placement();


};
