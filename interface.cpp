#include "interface.h"
#include <string>
using namespace std;

//Constructeurs

interface::interface()
{

}

interface::interface(int nb, int l, int h, int hauteur_marge, int h_tour, int l_tour, int e_case_tour, int argent)
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
    Argent=argent;
    nb_tour = 0;
    nb_proj = 0;
}

//Affichage en bas de l'écran

void interface::Affiche_nb_ennemi_restant()
{
    drawString(largeur*0.9,hauteur-taille_marge*0.25,"ENNEMIS",RED);
    drawString(largeur*0.9,hauteur-taille_marge*0.12,"RESTANTS",RED);
    fillRect(largeur*0.94,hauteur-taille_marge*0.45,largeur*0.94,taille_marge*0.40,couleur_arriere_plan);
    drawString(largeur*0.96,hauteur-taille_marge*0.15,std::to_string(nb_ennemi),ORANGE,30);
}
void interface::Affiche_argent()
{
    drawString(largeur*0.9,hauteur-taille_marge*0.75,"ARGENT",ORANGE);
    fillRect(largeur*0.94,hauteur-taille_marge*0.95,largeur*0.06,taille_marge*0.40,couleur_arriere_plan); //Efface l'ancienne valeur
    drawString(largeur*0.96,hauteur-taille_marge*0.65,std::to_string(Argent),ORANGE,30);//Affiche la nouvelle valeur

}

void interface::Affiche_case_tour(int &indice, grille g)
{
    //Dessine des cases
    drawRect(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, BLACK);
    //Dessine les tours et leur coûts
    if (indice<5)
    {
        fillRect(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour)+floor(g.get_taille_case()/2), hauteur-hauteur_case_tour-8+floor(g.get_taille_case()/3),g.get_taille_case(),g.get_taille_case(), couleur_tour[indice]);
        drawString(ecart_case_tour+indice*(largeur_case_tour+ecart_case_tour)+floor(1.8*g.get_taille_case()), hauteur-hauteur_case_tour-8+floor(g.get_taille_case()/3)+floor(g.get_taille_case()*0.7),std::to_string(cout_tour[indice]),BLACK,30);
    }
    drawString(ecart_case_tour+5*(largeur_case_tour+ecart_case_tour)+floor(0.5*g.get_taille_case()), hauteur-hauteur_case_tour-8+floor(g.get_taille_case()/3)+floor(g.get_taille_case()*0.7),"VENTE",BLACK,30);
    indice=-1;

    //On affiche aussi quelles tours sont achetables
    for (int n=0;n<5;n++)
    {
        dessine_argent_suffisant(cout_tour[n],n);
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


void interface::choisir_tour(int &n, tour liste_tours[], grille g, ennemi liste_ennemi[], point a)
{
    if (n==-1) //Si l'on n'a pas encore choisi quelle tour placee
    {
        point point;
        point=Souris_clique_gauche(); //Selection de la case de l'interface
        if ((point.x!=-1)&&(point.y!=-1))
        {
            n=case_selectionnees(point.x,point.y); //On voit quel case a ete selectionnee et on la met en vert
            drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, GREEN);
        }
    }
    else //Sinon, on s'interesse à la position de la tour
    {
        if(choisir_position_tour(n, liste_tours, g, liste_ennemi, a)) //Si la position de la tour est possible, on la place
        {
            Affiche_case_tour(n,g); //On deselectionne alors la case associee et la redessinant
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

bool interface::choisir_position_tour(int &n, tour liste_tours[], grille g, ennemi liste_ennemi[], point a)
{
    bool bien_place = false;
    bool place_sur_tour = false;
    if ((n>=0)&&(n<6)) //On verifie qu'une tour a bien ete selectionnee
    {
        point point;
        point=Souris_clique_gauche(); //Choix de la position
        if (((point.x>0)&&(point.x<g.get_taille_case()*(g.get_nb_largeur_case()-1))&&(point.y>0)&&(point.y<g.get_taille_case()*g.get_nb_hauteur_case()))) //On verifie que l'on a clique sur l'ecran de jeu
        {
            bien_place=g.get_libre_tour(g.get_place(point)); //On note si la case est libre
            place_sur_tour = not g.get_libre_ennemi(g.get_place(point));
            g.set_libre_ennemi(g.get_place(point), false);//La case n'est plus libre
            bool gene=verification_chemin(liste_ennemi, point, g, a); //On verifie que l'ajout de la tour n'empeche pas les ennemis d'atteindre leur destination

            if ((bien_place)&&(gene==false)&&(cout_tour[n]<=Argent)) //Achat d'une nouvelle tour
            {
                Argent-=cout_tour[n];//On enleve le cout à l'argent (pour l'instant n)
                for (int i=0;i<5;i++)
                {
                    dessine_argent_suffisant(cout_tour[i],i); //On revoit quelles tours sont achetables
                }
                g.set_libre_tour(g.get_place(point), false);
                liste_tours[nb_tour] = tour(point.x,point.y,n,g); //On dessine la tour
                nb_tour++;
            }
            else if(n==5 and place_sur_tour)//Vente de tour
            {
                for(int i=0; i<nb_tour; i++)
                {
                    if(g.get_pos(g.get_place(point))==liste_tours[i].get_pos())//Si l'on clique sur une tour existante après avoir cliqué sur la case vendre
                    {
                        Argent += floor(0.75*cout_tour[liste_tours[i].get_type()]); //On récupère 75% de l'argent dépensé
                        for (int j=0;j<5;j++)
                        {
                            dessine_argent_suffisant(cout_tour[j],j); //On revoit quelles tours sont achetables
                        }
                        //Il n'y a plus de tour sur la case, elle est à nouveau libre
                        g.set_libre_tour(g.get_place(point), true);
                        g.set_libre_ennemi(g.get_place(point), true);
                        liste_tours[i].efface(g);//On efface la tour et on la supprime de la liste
                        nb_tour--;
                        liste_tours[i] = liste_tours[nb_tour];
                        bien_place = true;
                    }
                }
            }
        }
        else if (((point.x>0)&&(point.x<largeur)&&(point.y>hauteur-taille_marge)&&(point.y<hauteur))||(n>Argent))
        {
            drawRect(ecart_case_tour+n*(largeur_case_tour+ecart_case_tour), hauteur-hauteur_case_tour-8,largeur_case_tour,hauteur_case_tour, BLACK);
            n=-1; // Si on clique à nouveau dans la zone inférieur, on déselectionne la tour (ou l'option vente).

        }
    }
    return bien_place;
}

bool interface::verification_chemin(ennemi liste_ennemi[], point p,  grille g, point a)
{
    bool bloque=false;

    //On teste les points de départs
    chemin c=chemin(g);//C'est un chemin fictif
    for (int i=0; i<g.get_nb_hauteur_case();i++)
    {
        point dep; // dep va valoir toutes les cases depuis lesquelles les ennemis arrivent
        dep.y=i;
        dep.x=g.get_nb_largeur_case()-1;
        if (c.Calcul_plus_court_chemin(dep,g,a)==false)
        {
            //Si l'un des points de départs n'est pas relié à l'arrivée à cause de cette nouvelle tour
            g.set_libre_ennemi(g.get_place(p), true); //On enleve cette tour
            bloque=true;
            return bloque;
        }
    }

    // On teste les ennemis present sur le terrain
    for (int i=0; i<nb_ennemi;i++)
    {
        if (liste_ennemi[i].get_dans_le_cadre())
        {
            if (liste_ennemi[i].Chemin_ennemi.Calcul_plus_court_chemin(g.get_indices_xy(g.get_place(liste_ennemi[i].get_position())),g,a)==false)
            {
                //L'un des ennemis se retrouve enfermé à cause de la nouvelle tour
                g.set_libre_ennemi(g.get_place(p), true);
                bloque=true;
                return bloque;
            }
        }
    }
    return bloque;
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
