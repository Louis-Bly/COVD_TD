#include "interface.h"
#include <string>
using namespace std;

//Constructeurs

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

//Affichage en bas de l'écran

void interface::Affiche_nb_ennemi_restant()
{
    drawString(largeur*0.9,hauteur-taille_marge*0.25,"ENNEMIS",RED);
    drawString(largeur*0.9,hauteur-taille_marge*0.12,"RESTANTS",RED);
    drawString(largeur*0.96,hauteur-taille_marge*0.15,std::to_string(nb_ennemi),ORANGE,30);
}
void interface::Affiche_argent()
{
    int taille_ecriture_argent=100;
    drawString(largeur*0.9,hauteur-taille_marge*0.75,"ARGENT",ORANGE);
    fillRect(largeur*0.94,hauteur-taille_marge*0.95,taille_ecriture_argent,taille_marge*0.40,couleur_arriere_plan);
    drawString(largeur*0.96,hauteur-taille_marge*0.65,std::to_string(Argent),ORANGE,30);

}

void interface::Affiche_case_tour(int &indice)
{
    //Dessine des cases
    drawRect(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, BLACK);
    indice=-1;

    //On affiche aussi quelles tours sont achetables
    for (int n=0;n<6;n++)
    {
        dessine_argent_suffisant(n,n);
    }
}

void interface::Affiche_marge()
{
    //Dessine les marges contenant la valeur de l'argent, le nombre d'ennemis restants, et les tours achetables
    int epaisseur_trait=4;
    drawLine(0,hauteur-taille_marge,largeur,hauteur-taille_marge,BLACK,epaisseur_trait);
    drawLine(largeur*0.89,hauteur-taille_marge,largeur*0.89,hauteur,BLACK,4);
    drawLine(largeur*0.89,hauteur-taille_marge/2+epaisseur_trait/2,largeur,hauteur-taille_marge/2+epaisseur_trait/2,BLACK,epaisseur_trait);
}


void interface::choisir_tour(int &n)
{
    if (n==-1) //Si l'on n'a pas encore choisi quelle tour placee
    {
        point point;
        point=Souris_clique_gauche(); //Selection de la case
        if ((point.x!=-1)&&(point.y!=-1))
        {
            n=case_selectionnees(point.x,point.y); //On voit quel case a ete selectionnee et on la met en vert
            drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, GREEN);
        }
    }
    else //Sinon, on s'interesse à la position de la tour
    {
        if(choisir_position_tour(n)) //Si la position de la tour est possible, on la place
        {
            Affiche_case_tour(n); //On deselectionne alors la case associee et la redessinant
        }
    }
}

int interface::case_selectionnees(int x, int y)
{
    int numero=-1; //Pas de case selectionnee
    if ((y>hauteur-hauteur_case_tour-15) && (y<hauteur-15)) //La hauteur correspond à celle des cases
    {
        for (int i=0;i<6;i++)
        {
            if ((x>ecart_case_tour+i*(largeur_case_tour+ecart_case_tour))&&(x<(i+1)*(largeur_case_tour+ecart_case_tour)))
            {
                numero=i; //Case i a ete choisie
            }
        }
    }
    return numero; //numero de la case
}

bool interface::choisir_position_tour(int &n)
{
    bool bien_place = false;
    if ((n>=0)&&(n<6)) //On verifie qu'une tour a bien ete selectionnee
    {
        point point;
        point=Souris_clique_gauche(); //Choix de la position
        if (((point.x>0)&&(point.x<largeur)&&(point.y>0)&&(point.y<hauteur-taille_marge))&&(n<=Argent)) //n sera à changer avec le prix de la tour ;;; On verifie que l'on a clique sur l'ecran de jeu
        {
            bien_place=true;
            if (bien_place)
            {
                Argent-=n;//On enleve le cout à l'argent (pour l'instant n)
                for (int i=0;i<6;i++)
                {
                    dessine_argent_suffisant(i,i); //On revoit quelles tours sont achetables
                }
                drawString(point.x,point.y,std::to_string(n),ORANGE,30); //On dessine la tour(pour l'instant des nombres)
            }
        }
        else if (((point.x>0)&&(point.x<largeur)&&(point.y>hauteur-taille_marge)&&(point.y<hauteur))||(n>Argent))
        {
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



void interface::dessine_argent_suffisant(int cout, int n) //Indique quelles tours sont disponibles
{
    if (cout>Argent)//Indique qu'il n'est pas possible de l'acheter
    {
        drawString(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour)+40,hauteur-taille_marge+20,"Argent insuffisant",RED);
    }
    else //Indique qu'il est possible de l'acheter
    {
        fillRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-36,largeur_case_tour,22, couleur_arriere_plan);
    }
}


//Test
void interface::liste_test(point position_origine_b,point position_origine_r,point position_origine_a,point position_origine_t)
{
    liste_ennemi[0]=ennemi_basique(position_origine_b);
    liste_ennemi[1]=ennemi_rapide(position_origine_r);
    liste_ennemi[2]=ennemi_ameliore(position_origine_a);
    liste_ennemi[3]=ennemi_tank(position_origine_t);
}
