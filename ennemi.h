#pragma once

#include "chemin.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

//On définit une classe ennemi
class ennemi
{

    //Parametres fixes
    int vitesse;
    int vie_max; //Vie initiale
    int recompense; //Argent reçu lors de sa mort
    int Hauteur_barre_vie; //Ecart entre le perso et sa barre de vie (entre les 2 centres respectifs)

    //Parametres variables
    point position;
    int hp; //Vie actuelle
    bool vivant;
    chemin Chemin;

    //Forme de l'ennemi (à modifier à la fin)
    int Rayon; //Rayon du cercle (pour l'instant, les ennemis sont des cercles)
    point Taille_barre_vie; // x représente la demi-largeur, y la demi-hauteur.
    Color couleur;

    //Fonctions
public:

    //Constructeur
    ennemi();
    ennemi(int vitesse, int vie, int recompense,int Hauteur_barre_vie, point position_origine, point barre_vie, Color col, int R);

    //Affichages
    void Affiche_ennemi();
    void Efface_ennemi();
    void Affiche_barre_vie();
    void Efface_barre_vie();

    //Deplacement
    void Deplace(); //Calcul la direction et deplace

    //Gestion de la vie
    bool Perte_vie(int degats_subis, int &Argent, int indice, int &nb_ennemi, ennemi* &liste); //Prends en paramètre un bool d'une fonction de projectile.h (si est touche)
    bool Mort(int &Argent, int indice, int &nb_ennemi, ennemi* &liste); //Indice servira lorsqu'on aura cree la liste d'ennemis

    //Fonctions Get
    point get_position(){return position;};
    int get_rayon(){return Rayon;};
    int get_vie_max(){return vie_max;};
    int get_hp(){return hp;};
    int get_vitesse(){return vitesse;};


};

// Types d'ennemis

ennemi ennemi_basique(point position_origine);
ennemi ennemi_ameliore(point position_origine);
ennemi ennemi_rapide(point position_origine);
ennemi ennemi_tank(point position_origine);

