#include "menu_principal.h"
int main()
{
    const int largeur_fenetre = 1900;
    const int hauteur_fenetre = 1000;
    const int marge_cote = 400;
    int taille_tour=75;
    Menu M(largeur_fenetre, hauteur_fenetre, marge_cote, taille_tour);
    M.Menu_principal();
    return 0;
}
