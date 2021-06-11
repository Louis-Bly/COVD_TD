#include "ennemi.h"

//Constructeur

ennemi::ennemi()
{

}

ennemi::ennemi(int vite, int vie_init, int reward, int Hauteur, point position_origine, point Dimension_barre_vie, Color col, int R, grille G)
{
    vitesse=vite;
    temps_de_changement_de_direction=floor(G.get_taille_case()/(2*vite)); //Permet à l'ennemi de tourner au milieu de la case
    vie_max=vie_init;
    hp=vie_init;
    recompense=reward;
    Hauteur_barre_vie=Hauteur;
    position=position_origine;
    couleur=col;
    Rayon=R;
    Taille_barre_vie=Dimension_barre_vie;
    vivant=true;
    Chemin_ennemi=chemin(G);
    dans_le_cadre=false;
    direction_actuelle=2; //L'ennemi arrive de la droite de l'écran
    temps=0;
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
void ennemi::Deplace(grille Grille, point arrivee) //Calcul la direction et deplace
{
    Efface_ennemi();
    Efface_barre_vie();
    if (dans_le_cadre==false)//Avant d'apparaître à l'écran
    {
        position.x-=vitesse; // Il avance en ligne droite jusqu'à arriver dans la zone de jeu
        entre_dans_le_cadre(Grille, arrivee); //On regarde s'il est arrivé
    }
    else
    {
        //L'ennemi est présent, il se déplace selon l'algorithme de plus court chemin
        Grille.set_libre_tour(Grille.get_place(position),true);//La case sur laquelle il est devient libre pour placer des tours
        position.x+=dir[direction_actuelle].x*vitesse; //L'ennemi avance
        position.y+=dir[direction_actuelle].y*vitesse;
        Grille.set_libre_tour(Grille.get_place(position),false);//La case sur laquelle il arrive n'est plus libre pour placer des tours
        changement_de_case(Grille);
    }

    Affiche_ennemi();
    Affiche_barre_vie();
}

void ennemi::entre_dans_le_cadre(grille Grille, point arrivee) //Attention, x et y du point d'arrivée ne sont pas ses coordonnées en terme de pixel mais le numéro de ligne/colonne
{
    if (position.x<Grille.get_taille_case()*Grille.get_nb_largeur_case()) //L'ennemi est entré dans l'écran.
    {
        dans_le_cadre=true;
        int indice_pos=Grille.get_place(position);
        case_actuelle=Grille.get_indices_xy(indice_pos); //colonne et ligne de la nouvelle case
        Chemin_ennemi.Calcul_plus_court_chemin(case_actuelle,Grille,arrivee); //on calcul le chemin à suivre
        changement_de_direction(Grille); //calcul de la direction à prendre jusqu'à la prochaine case

    }
}



void ennemi::changement_de_direction(grille G) //Utilisé lors de l'entrée dans la grille ou lors d'un changement de case
{
    int indice_case_suivante=Chemin_ennemi.get_chemin_de_ennemi(Chemin_ennemi.get_taille_chemin()-1); //On note la case où l'ennemi doit se rendre
    point case_suivante=G.get_indices_xy(indice_case_suivante);
    G.set_libre_tour(indice_case_suivante,false); //Cette case n'est plus libre pour les tours puisque l'ennemi s'est engagé sur cette case
    //On regarde où se situe cette case par rapport à la position actuelle de l'ennemi
    if(case_suivante.x==case_actuelle.x+1)
    {
        direction_actuelle=0;
    }
    else if(case_suivante.y==case_actuelle.y+1)
    {
        direction_actuelle=1;
    }
    else if(case_suivante.x==case_actuelle.x-1)
    {
        direction_actuelle=2;
    }
    else if(case_suivante.y==case_actuelle.y-1)
    {
        direction_actuelle=3;
    }
    int c=Chemin_ennemi.get_taille_chemin(); //On enlève la case actuelle du chemin
    Chemin_ennemi.set_taille_chemin(Chemin_ennemi.get_taille_chemin()-1);
    c=Chemin_ennemi.get_taille_chemin();
}

void ennemi::changement_de_case(grille G)
{
    int indice_pos=G.get_place(position);
    point nouvelle_case=G.get_indices_xy(indice_pos);
    if ((nouvelle_case.x!=case_actuelle.x)||(nouvelle_case.y!=case_actuelle.y)) //Lorsque l'ennemi vient de changer de case
    {
        if (temps<temps_de_changement_de_direction)
        {
            temps++; //On laisse l'ennemi continuer dans sa direction actuelle jusqu'à ce qu'il atteigne le milieu de sa case
        }
        else //Il est au milieu de sa case
        {
            temps=0; //On réinitialise temps pour qu'il continue d'aller de milieu de case en mileu de case
            case_actuelle.x=nouvelle_case.x;//La case de l'ennemi a changé
            case_actuelle.y=nouvelle_case.y;

            changement_de_direction(G); //Il faut calculer sa nouvelle direction
        }
    }
}

//Gestion de la vie


void ennemi::Mort(int &Argent, int indice, int &nb_ennemi, ennemi *&liste) //nb_ennemi est defini dans chemin, lorsqu'il tombe à 0 la partie s'est gagné
{
    if (hp==0) //Plus de vie
    {
        Efface_ennemi();
        Efface_barre_vie();
        vivant=false;
        Argent+=recompense;//L'argent augmente
        nb_ennemi--; //Le nombre d'ennemis restants baisse

        liste[indice]=liste[nb_ennemi];
    }
}

void ennemi::Perte_vie(int degats_subis, int &Argent, int indice, int &nb_ennemi, ennemi *&liste) //Prends en paramètre la valeur des dégats recus, retourne vrai si l'ennemi meurt de ses blessures
{
    hp-=degats_subis;//Perte de vie
    if (hp<0) //S'il meurt, sa vie est à 0
    {
        hp=0;
    }
    //On regarde si l'ennemi meurt
    Mort(Argent, indice, nb_ennemi,liste);
}

// Types d'ennemis

ennemi ennemi_basique(point position_origine, grille G)
{
    //Variables
    int vite=5;
    int vie_init=100;
    int recompense=15;
    int H=40;
    point Dimension_barre_vie;
    Dimension_barre_vie.x=15;
    Dimension_barre_vie.y=5;
    Color col=YELLOW;
    int R=20;

    //Appele du constructeur
    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R, G);
    return E;
}

ennemi ennemi_ameliore(point position_origine, grille G)
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

        ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R, G);
        return E;
    }
}

ennemi ennemi_rapide(point position_origine, grille G)
{
    int vite=10;
    int vie_init=50;
    int recompense=5;
    int H=40;
    point Dimension_barre_vie;
    Dimension_barre_vie.x=15;
    Dimension_barre_vie.y=5;
    Color col=BLUE;
    int R=20;

    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R, G);
    return E;
}
ennemi ennemi_tank(point position_origine, grille G)
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

    ennemi E=ennemi(vite, vie_init, recompense, H, position_origine, Dimension_barre_vie, col, R, G);
    return E;
}
