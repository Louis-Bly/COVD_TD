#include "chemin.h"
#include <string>
using namespace std;

interface::interface(int nb, int l, int h, int hauteur_marge, int h_tour, int l_tour, int e_case_tour)
{
    hauteur=h;
    largeur=l;

    taille_marge=hauteur_marge;
    hauteur_case_tour=h_tour;
    largeur_case_tour=l_tour;
    ecart_case_tour=e_case_tour;

    nb_ennemi_initial=nb;
    nb_ennemi=nb;
    Argent=0;
    //liste_ennemi=new ennemi[nb];
}




void interface::Affiche_nb_ennemi_restant()
{
    drawString(largeur-180,hauteur-taille_marge*0.25,"ENNEMIS",RED);
    drawString(largeur-180,hauteur-taille_marge*0.12,"RESTANTS",RED);
    drawString(largeur-50,hauteur-taille_marge*0.15,std::to_string(nb_ennemi),ORANGE,30);
}
void interface::Affiche_argent()
{
    drawString(largeur-180,hauteur-taille_marge*0.75,"ARGENT",ORANGE);
    drawString(largeur-50,hauteur-taille_marge*0.65,std::to_string(Argent),ORANGE,30);

}

void interface::Affiche_case_tour(int indice)
{
    drawRect(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-15,largeur_case_tour,hauteur_case_tour, BLACK);
}

void interface::Affiche_marge()
{
    drawLine(0,hauteur-taille_marge,largeur,hauteur-taille_marge,BLACK,4);
    drawLine(largeur-200,hauteur-taille_marge,largeur-200,hauteur,BLACK,4);
    drawLine(largeur-200,hauteur-taille_marge/2+2,largeur,hauteur-taille_marge/2+2,BLACK,4);
}


int interface::choisir_tour()
{
    int x; int y;
    int k=getMouse(x,y);
    int n=-1;
    if (k==1)
    {
        n=case_selectionnees(x,y);
        drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-15,largeur_case_tour,hauteur_case_tour, GREEN);
    }
    choisir_position_tour(n);
    Affiche_case_tour(n);
}

int interface::case_selectionnees(int x, int y)
{
    int numero=-1;
    if ((y>hauteur-hauteur_case_tour-15) && (y<hauteur-15))
    {
        for (int i=0;i<6;i++)
        {
            if ((x>ecart_case_tour+i*(largeur_case_tour+ecart_case_tour))&&(x<(i+1)*(largeur_case_tour+ecart_case_tour)))
            {
                numero=i;
            }
        }
    }
    return numero;
}

void interface::choisir_position_tour(int n)
{
    if ((n>=0)&&(n<6))
    {
        int x; int y;
        int k=getMouse(x,y);
        if (k==1)
        {
            fillCircle(x,y,5,GREEN);
            bool confirmer=confirmer_placement();
            fillCircle(x,y,5,WHITE);
            if (confirmer)
            {
                drawString(x,y,std::to_string(n),ORANGE,30);
            }
        }
    }
}

bool interface::confirmer_placement()
{
    int x; int y;
    int k=getMouse(x,y);
    if (k==1)
    {
        return true;
    }
    return false;
}
