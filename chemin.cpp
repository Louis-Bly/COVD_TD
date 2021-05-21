#include "chemin.h"

chemin::chemin(int l, int h, int taille_case)
{
    taille_carre_grille=taille_case;
    nb_largeur_case=l/taille_carre_grille;
    nb_hauteur_case=h/taille_carre_grille;
    libre=new bool[nb_hauteur_case*nb_largeur_case];
    for (int i=0;i<nb_hauteur_case*nb_largeur_case;i++)
    {
        libre[i]=true;
    }
}
