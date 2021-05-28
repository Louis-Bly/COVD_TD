#include "ennemi.h"

//Constructeur

ennemi::ennemi()
{

}

ennemi::ennemi(int vite, int vie_init, int reward, int Hauteur, point position_origine, point Dimension_barre_vie, Color col, int R)
{
    vitesse=vite;
    vie_max=vie_init;
    hp=vie_init;
    recompense=reward;
    Hauteur_barre_vie=Hauteur;
    position=position_origine;
    couleur=col;
    Rayon=R;
    Taille_barre_vie=Dimension_barre_vie;
    vivant=true;
}

//Affichages
void ennemi::Affiche_ennemi()
{
    fillCircle(position.x, position.y, Rayon, couleur);
}

void ennemi::Efface_ennemi()
{
    fillCircle(position.x, position.y, Rayon, WHITE);
}

void ennemi::Affiche_barre_vie()
{
    //Intérieur:
    int pourcentage=ceil(hp*2*Taille_barre_vie.x/vie_max);
    fillRect(position.x-Taille_barre_vie.x, position.y-Hauteur_barre_vie+Taille_barre_vie.y, pourcentage, 2*Taille_barre_vie.y, GREEN);
    //Contour:
    drawRect(position.x-Taille_barre_vie.x, position.y-Hauteur_barre_vie+Taille_barre_vie.y, 2*Taille_barre_vie.x, 2*Taille_barre_vie.y, BLACK);
}

void ennemi::Efface_barre_vie()
{
    fillRect(position.x-Taille_barre_vie.x, position.y-Hauteur_barre_vie+Taille_barre_vie.y, 2*Taille_barre_vie.x+1, 2*Taille_barre_vie.y+1, WHITE);
}

//Deplacement
void ennemi::Deplace() //Calcul la direction et deplace
{
    //On calculera le plus court chemin avec A* plus tard...
    //Pour l'instant on se contente d'une ligne droite
    Efface_ennemi();
    Efface_barre_vie();
    position.x-=vitesse;
    Affiche_ennemi();
    Affiche_barre_vie();
}


//Gestion de la vie


bool ennemi::Mort(int &Argent, int indice, int &nb_ennemi, ennemi *&liste) //nb_ennemi est defini dans chemin, lorsqu'il tombe à 0 la partie s'est gagné
{
    if (hp==0)
    {
        Efface_ennemi();
        Efface_barre_vie();
        vivant=false;
        Argent+=recompense;
        nb_ennemi--;

        liste[indice]=liste[nb_ennemi];
        return vivant;
    }
}

bool ennemi::Perte_vie(int degats_subis, int &Argent, int indice, int &nb_ennemi, ennemi *&liste) //Prends en paramètre la valeur des dégats recus, retourne vrai si l'ennemi meurt de ses blessures
{
    hp-=degats_subis;
    if (hp<0)
    {
        hp=0;
    }
    //On regarde si l'ennemi meurt
    return Mort(Argent, indice, nb_ennemi,liste);
}

// Types d'ennemis

ennemi ennemi_basique(point position_origine)
{
    int vite=5;
    int vie_init=100;
    int recompense=15;
    int H=40;
    point Dimension_barre_vie;
    Dimension_barre_vie.x=15;
    Dimension_barre_vie.y=5;
    Color col=YELLOW;
    int R=20;

    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R);
    return E;
}

ennemi ennemi_ameliore(point position_origine)
{
    {
        int vite=6;
        int vie_init=150;
        int recompense=20;
        int H=40;
        point Dimension_barre_vie;
        Dimension_barre_vie.x=15;
        Dimension_barre_vie.y=5;
        Color col=RED;
        int R=20;

        ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R);
        return E;
    }
}

ennemi ennemi_rapide(point position_origine)
{
    int vite=15;
    int vie_init=50;
    int recompense=5;
    int H=40;
    point Dimension_barre_vie;
    Dimension_barre_vie.x=15;
    Dimension_barre_vie.y=5;
    Color col=BLUE;
    int R=20;

    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R);
    return E;
}
ennemi ennemi_tank(point position_origine)
{
    int vite=2;
    int vie_init=500;
    int recompense=30;
    int H=40;
    point Dimension_barre_vie;
    Dimension_barre_vie.x=15;
    Dimension_barre_vie.y=5;
    Color col=GREEN;
    int R=20;

    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R);
    return E;
}
