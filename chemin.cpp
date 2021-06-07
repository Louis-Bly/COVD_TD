#include "chemin.h"

chemin::chemin()
{

}

chemin::chemin(grille G)
{
    direction= new point[G.get_nombre_case()];
    cout_des_cases=new int[G.get_nombre_case()];
    chemin_de_ennemi=new int[G.get_nombre_case()];
    taille_chemin=0;
}

bool chemin::Calcul_plus_court_chemin(point position,grille Grille, point arrivee) //Point arrivee/depart et le numero de ligne/colonne
{

    //On met à jour le cout d'accès au case

    //Définition des variables
    int indice_case_init= Grille.get_indices(position);
    int indice_case_arrivee=Grille.get_indices(arrivee);
    int *cout_estime=new int[Grille.get_nombre_case()]; //cout heuristique permettant d'orienter la recherche dans la bonne direction
    int *cout_partiel=new int[Grille.get_nombre_case()];// Aller de o à i
    int *cout_acces=new int [Grille.get_nombre_case()]; //Venir sur i depuis un voisin
    int *cout_total=new int[Grille.get_nombre_case()];// cout partiel + cout heuristique
    int *predecesseur=new int[Grille.get_nombre_case()]; // Le i^ème contient l'indice du prédécesseur de la i^ème case

    point* coord=new point[Grille.get_nombre_case()]; //Contient les coordonnées x,y de la case(x=0 à nb_largeur_case)

    //Initialisation des couts
    for (int i=0;i<Grille.get_nombre_case();i++)
    {
        coord[i]=Grille.get_indices_xy(i);
        cout_estime[i]=abs(coord[i].x-arrivee.x)+abs(coord[i].y-arrivee.y);
        if (Grille.get_libre_ennemi(i))
        {
            cout_acces[i]=1;
        }
        else
        {
            cout_acces[i]=1000000;
        }
        cout_partiel[i]=Grille.get_nombre_case()*10;
        cout_total[i]=Grille.get_nombre_case()*10;
    }
    cout_partiel[indice_case_init]=0;
    cout_total[indice_case_init]=cout_estime[indice_case_init]+cout_partiel[indice_case_init];

    // Definition des points en cours de traitement(pour l'instant une liste, plus tard une file de priorité)
    int* liste_case_active=new int[Grille.get_nombre_case()];
    int nb_case_active=1; //A l'initialisation, il n'y a que le point de départ
    liste_case_active[0]=indice_case_init;
    int case_active;
    bool arrive=false;
    while ((nb_case_active>0)&&(arrive==false)) //Coeur du A*
    {
        case_active=liste_case_active[0];
        for (int j=0; j<4;j++)
        {
            point nouveau;
            nouveau.x=Grille.get_indices_xy(case_active).x+dir[j].x;
            nouveau.y=Grille.get_indices_xy(case_active).y+dir[j].y;
            int x=nouveau.x; //Pour debuguer
            int y=nouveau.y; //Pour debuguer
            int nouveau_indice= Grille.get_indices(nouveau);
            if((nouveau.x>=1)&&(nouveau.y>=0)&&(nouveau.x<Grille.get_nb_largeur_case())&&(nouveau.y<Grille.get_nb_hauteur_case())&&(Grille.get_libre_ennemi(nouveau_indice)))//Test si la case est sur la grille et si elle n'a pas de tour
            { // On a bien un successeur.
                if (cout_partiel[nouveau_indice]>cout_partiel[case_active]+cout_acces[nouveau_indice]) // On regarde si le cout pour aller de o à case_active + celui pour aller sur nouveau (voisin de case_active) est inférieur à celui trouvé précedement pour aller de o à nouveau
                {
                    predecesseur[nouveau_indice]=case_active; //On note le prédecesseur pour pouvoir remonter à la fin
                    cout_partiel[nouveau_indice]=cout_partiel[case_active]+1;//Grille.get_cout_des_cases(nouveau_indice);
                    cout_total[nouveau_indice]=cout_partiel[nouveau_indice]+cout_estime[nouveau_indice];

                    int cpa=cout_partiel[case_active];
                    int l=cout_acces[nouveau_indice];
                    int cp=cout_partiel[nouveau_indice];
                    int ce=cout_estime[nouveau_indice];
                    int cout=cout_total[nouveau_indice]; //Pour debuguer

                    //On ajoute nouveau à la liste des cases actives
                    if (indice_case_arrivee==nouveau_indice)
                    {
                        arrive=true;
                    }
                    else
                    {
                        bool deja_presente=false; // Indique si nouveau est dans liste_case_active
                        for (int i=0; i<nb_case_active;i++)
                        {
                            if (liste_case_active[i]==nouveau_indice)
                            {
                                deja_presente=true;
                                while((i>1)&&(cout_total[i]<cout_total[i-1])) // On replace cet element, le 0^ème étant le point actif, on ne le compare pas
                                {
                                    liste_case_active[i]=liste_case_active[i-1];
                                    liste_case_active[i-1]=nouveau_indice;
                                    i-=1;
                                }
                                break;
                            }
                        }
                        if (deja_presente==false)
                        {
                            liste_case_active[nb_case_active]=nouveau_indice;
                            int pos=nb_case_active;
                            nb_case_active+=1;
                            while((pos>1)&&(cout_total[liste_case_active[pos]]<cout_total[liste_case_active[pos-1]])) // On replace cet element
                            {
                                liste_case_active[pos]=liste_case_active[pos-1];
                                liste_case_active[pos-1]=nouveau_indice;
                                pos-=1;
                            }
                        }
                    }
                }
            }
        }
        // Calcul du futur point actif
        nb_case_active-=1;
        for (int i=0;i<nb_case_active;i++)
        {
            liste_case_active[i]=liste_case_active[i+1];
        }
    }
    if (arrive)
    {
        int i=0;
        int indice=indice_case_arrivee;
        while(indice!=indice_case_init)
        {
            chemin_de_ennemi[i]=indice;
            indice=predecesseur[indice];
            taille_chemin++;
        }
    }
    return arrive;
}
