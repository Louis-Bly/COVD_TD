#include "interface.h"
#include <string>
using namespace std;

interface::interface()
{

}

interface::interface(int nb, int l, int h, int hauteur_marge, int h_tour, int l_tour, int e_case_tour)
{
    hauteur=h;
    largeur=l;

    couleur_arriere_plan=WHITE;

    taille_marge=hauteur_marge;
    hauteur_case_tour=h_tour;
    largeur_case_tour=l_tour;
    ecart_case_tour=e_case_tour;

    nb_ennemi_initial=nb;
    nb_ennemi=nb;
    Argent=0;
    liste_ennemi=new ennemi[nb];
}




void interface::Affiche_nb_ennemi_restant()
{
    drawString(largeur-180,hauteur-taille_marge*0.25,"ENNEMIS",RED);
    drawString(largeur-180,hauteur-taille_marge*0.12,"RESTANTS",RED);
    drawString(largeur-75,hauteur-taille_marge*0.15,std::to_string(nb_ennemi),ORANGE,30);
}
void interface::Affiche_argent()
{
    drawString(largeur-180,hauteur-taille_marge*0.75,"ARGENT",ORANGE);
    fillRect(largeur-115,hauteur-taille_marge*0.95,100,taille_marge*0.40,couleur_arriere_plan);
    drawString(largeur-75,hauteur-taille_marge*0.65,std::to_string(Argent),ORANGE,30);

}

void interface::Affiche_case_tour(int &indice)
{
    drawRect(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, BLACK);
    indice=-1;
}

void interface::Affiche_marge()
{
    drawLine(0,hauteur-taille_marge,largeur,hauteur-taille_marge,BLACK,4);
    drawLine(largeur-200,hauteur-taille_marge,largeur-200,hauteur,BLACK,4);
    drawLine(largeur-200,hauteur-taille_marge/2+2,largeur,hauteur-taille_marge/2+2,BLACK,4);
}


void interface::choisir_tour(int &n)
{
    if (n==-1)
    {
        point point;
        point=Souris_clique_gauche();
        if ((point.x!=-1)&&(point.y!=-1))
        {
            n=case_selectionnees(point.x,point.y);
            drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, GREEN);
        }
    }
    else
    {
        if(choisir_position_tour(n))
        {
            Affiche_case_tour(n);
        }
    }
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

bool interface::choisir_position_tour(int &n)
{
    bool bien_place = false;
    if ((n>=0)&&(n<6))
    {
        point point;
        point=Souris_clique_gauche();
        if (((point.x>0)&&(point.x<largeur)&&(point.y>0)&&(point.y<hauteur-taille_marge))&&(n<=Argent)) //n sera à changer avec le prix de la tour
        {
            bien_place=true;
            if (bien_place)
            {
                //Calcul de la case occupée
                //int i=floor(x/c.taille_carre_grille);
                //int j=floor(y/c.taille_carre_grille);
                Argent-=n;

                drawString(point.x,point.y,std::to_string(n),ORANGE,30);
            }
        }
        else if (((point.x>0)&&(point.x<largeur)&&(point.y>hauteur-taille_marge)&&(point.y<hauteur))||(n>Argent))
        {
            if (n>Argent)
            {
                drawString(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour)+40,hauteur-taille_marge+20,"Argent insuffisant",RED);
            }
            drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, BLACK);
            n=-1; // Si on clique à nouveau dans la zone inférieur, on déselectionne la tour.

        }
    }
    return bien_place;
}

bool interface::confirmer_placement() //Ne sert à rien
{
    point p=Souris_clique_gauche();
    if ((p.x!=-1) && (p.y!=-1))
    {
        return true;
    }
    return false;
}

void interface::liste_test(point position_origine_b,point position_origine_r,point position_origine_a,point position_origine_t)
{
    liste_ennemi[0]=ennemi_basique(position_origine_b);
    liste_ennemi[1]=ennemi_rapide(position_origine_r);
    liste_ennemi[2]=ennemi_ameliore(position_origine_a);
    liste_ennemi[3]=ennemi_tank(position_origine_t);
}
