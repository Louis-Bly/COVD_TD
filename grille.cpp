#include "grille.h"

grille::grille(int l, int h, int taille_case_i)
{
    taille_case=taille_case_i;
    nb_largeur_case=l/taille_case;
    nb_hauteur_case=h/taille_case;
    libre_tour=new bool[get_nombre_case()];
    cout_des_cases=new int[get_nombre_case()];
    for (int i=0;i<nb_hauteur_case*nb_largeur_case;i++)
    {
        libre_tour[i]=true;
    }
}

void grille::affiche(){
    for(int i=1;i<nb_largeur_case;i++){
        drawRect(i*taille_case,0,1,taille_case*nb_hauteur_case,YELLOW);
    }
    for(int j=1;j<nb_hauteur_case; j++){
        drawRect(0,j*taille_case,taille_case*nb_largeur_case,1,YELLOW);
    }
}

int grille::get_place(point pos){
    return floor(pos.x/taille_case)+nb_largeur_case*floor(pos.y/taille_case);
}

point grille::get_pos(int place){
    point p;
    p.x = place%nb_largeur_case;
    p.y = floor(place/nb_largeur_case);
    return p;
}

point grille::get_indices_xy(int place)
{
    point p;
    p.x = place%nb_largeur_case;
    p.y = floor(place/nb_largeur_case);
    return p;
}

int grille::get_indices(point xy)
{
    return xy.x+nb_largeur_case*xy.y;
}

void grille::ajout_tour(int place){
    libre_tour[place] = false;
}

void grille::maj_cout_des_cases()
{
    for (int i=0;i<get_nombre_case();i++)
    {
        if (libre_ennemi[i])
        {
            cout_des_cases[i]=1;
        }
        else
        {
            cout_des_cases[i]=get_nombre_case()*10;
        }
    }
}
