#pragma once

#include "chemin.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

//On définit une classe ennemi
class ennemi
{

    //Parametres fixes
    int vitesse;
    int temps_de_changement_de_direction; //Correspond au temps entre l'entrée dans une nouvelle case et le changement de direction
    int temps; //temps depuis l'entrée dans une nouvelle case sans avoir tourné

    int vie_max; //Vie initiale
    int recompense; //Argent reçu lors de sa mort
    int Hauteur_barre_vie; //Ecart entre le perso et sa barre de vie (entre les 2 centres respectifs)

    //Parametres variables
    point position;
    int hp; //Vie actuelle
    bool vivant;

    bool dans_le_cadre;
    int direction_actuelle; //1: va vers la droite; 2: descend; 3: vers la gauche; 4:monte
    point case_actuelle; //Contient les numéros de lignes/colonnes de la case sur laquelle l'ennemi se trouve

    //Forme de l'ennemi (à modifier à la fin)
    int Rayon; //Rayon du cercle (pour l'instant, les ennemis sont des cercles)
    point Taille_barre_vie; // x représente la demi-largeur, y la demi-hauteur.
    Color couleur;

    //Fonctions
public:
    chemin Chemin_ennemi;
    //Constructeur
    ennemi();
    ennemi(int vitesse, int vie, int recompense,int Hauteur_barre_vie, point position_origine, point barre_vie, Color col, int R, grille G);

    //Affichages
    void Affiche_ennemi();
    void Efface_ennemi();
    void Affiche_barre_vie();
    void Efface_barre_vie();

    //Deplacement
    void Deplace(grille Grille, point arrivee); //Calcul la direction et deplace
    void entre_dans_le_cadre(grille Grille, point arrivee);
    void changement_de_direction(grille G);
    void changement_de_case(grille G);

    //Gestion de la vie
    void Perte_vie(int degats_subis, int &Argent, int indice, int &nb_ennemi, ennemi* &liste); //Prends en paramètre un bool d'une fonction de projectile.h (si est touche)
    void Mort(int &Argent, int indice, int &nb_ennemi, ennemi* &liste); //Indice servira lorsqu'on aura cree la liste d'ennemis

    //Fonctions Get
    point get_position(){return position;};
    int get_rayon(){return Rayon;};
    int get_vie_max(){return vie_max;};
    int get_hp(){return hp;};
    int get_vitesse(){return vitesse;};
    int get_temps_de_changement_de_direction(){return temps_de_changement_de_direction;};
    int get_temps(){return temps;};
    bool get_dans_le_cadre(){return dans_le_cadre;};
    point get_case_actuelle(){return case_actuelle;};

    void set_temps(int t){temps=t;};


};

// Types d'ennemis

ennemi ennemi_basique(point position_origine, grille G);
ennemi ennemi_ameliore(point position_origine, grille G);
ennemi ennemi_rapide(point position_origine, grille G);
ennemi ennemi_tank(point position_origine, grille G);

