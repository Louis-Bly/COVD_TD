#include "chemin.h"

chemin::chemin()
{

}

chemin::chemin(grille G)
{
    direction= new point[G.get_nombre_case()]; //On sait que la taile du chemin ne dépassera pas le nombre de cases
    chemin_de_ennemi=new int[G.get_nombre_case()];
    taille_chemin=0;
}

chemin::~chemin()
{

}

bool chemin::Calcul_plus_court_chemin(point position,grille Grille, point arrivee) //Point arrivee/depart et le numero de ligne/colonne
{
    //Définition des variables


    int indice_case_init= Grille.get_indices(position); //On récupère l'indice de la case correspondant au point d'arrivée et au point de départ.
    int indice_case_arrivee=Grille.get_indices(arrivee);

    //Définition des différents couts
    int cout_estime[Grille.get_nombre_case()]; //cout heuristique permettant d'orienter la recherche dans la bonne direction
    int cout_partiel[Grille.get_nombre_case()];// Aller de l'origine à la case i
    int cout_acces[Grille.get_nombre_case()]; //Venir sur i depuis un de ses 4 voisins
    int cout_total[Grille.get_nombre_case()];// cout partiel + cout heuristique
    int predecesseur[Grille.get_nombre_case()]; // Le i^ème contient l'indice du prédécesseur de la i^ème case

    point coord[Grille.get_nombre_case()]; //Contient les coordonnées x,y de la case(x=0 à nb_largeur_case)

    //Initialisation des couts d'acces aux cases en fonction du placement des tours
    for (int i=0;i<Grille.get_nombre_case();i++)
    {
        coord[i]=Grille.get_indices_xy(i);
        cout_estime[i]=abs(coord[i].x-arrivee.x)+abs(coord[i].y-arrivee.y); //Le cout estim
        if (Grille.get_libre_ennemi(i))
        {
            cout_acces[i]=1; // Il n'y a pas de tour, le cout est de 1
        }
        else
        {
            cout_acces[i]=1000000; //Présence de tour= cout eleve (en réalité, ces cases ne sont jamais testées ici grace à une boucle if plus loin)
        }
        cout_partiel[i]=Grille.get_nombre_case()*10; //On fixe un cout très grand pour que la première fois que le chemin croise ces cases, on soit sur de les ajouter à la liste des cases en cours de traitement
        cout_total[i]=Grille.get_nombre_case()*10;
    }
    cout_partiel[indice_case_init]=0; // Aller de l'origine à l'origine a un cout nul
    cout_total[indice_case_init]=cout_estime[indice_case_init]+cout_partiel[indice_case_init];

    // Definition des points en cours de traitement
    int liste_case_active[Grille.get_nombre_case()];
    int nb_case_active=1; //A l'initialisation, il n'y a que le point de départ
    liste_case_active[0]=indice_case_init;
    int case_active;
    bool arrive=false;
    while ((nb_case_active>0)&&(arrive==false)) //Coeur du A*
    {
        case_active=liste_case_active[0]; //Le premier élément de la liste est celui dont le cout actuelle est le plus faible, on commence donc par le traiter
        int dir_voisin_init=rand()%4; //On ajoute un paramètre aléatoire dans l'ordre de visite des voisins pour que les trajectoires ne soit pas trop prévisibles
        for (int j=dir_voisin_init; j<4+dir_voisin_init;j++)
        {
            point nouveau; //Nouveau est un voisin de case active
            nouveau.x=Grille.get_indices_xy(case_active).x+dir[j%4].x;
            nouveau.y=Grille.get_indices_xy(case_active).y+dir[j%4].y;
            int nouveau_indice= Grille.get_indices(nouveau);
            if((nouveau.x>=0)&&(nouveau.y>=0)&&(nouveau.x<Grille.get_nb_largeur_case())&&(nouveau.y<Grille.get_nb_hauteur_case())&&(Grille.get_libre_ennemi(nouveau_indice)))//Test si la case est sur la grille et si elle n'a pas de tour
            { // On a bien un successeur.
                if (cout_partiel[nouveau_indice]>cout_partiel[case_active]+cout_acces[nouveau_indice]) // On regarde si le cout pour aller de o à case_active + celui pour aller sur nouveau (voisin de case_active) est inférieur à celui trouvé précedement pour aller de o à nouveau
                {
                    predecesseur[nouveau_indice]=case_active; //On note le prédecesseur pour pouvoir remonter à la fin
                    cout_partiel[nouveau_indice]=cout_partiel[case_active]+cout_acces[nouveau_indice];//On définit le nouveau cout pour aller de l'origine à nouveau_indice à partir de case_active
                    cout_total[nouveau_indice]=cout_partiel[nouveau_indice]+cout_estime[nouveau_indice]; // On trouve alors un nouveau cout

                    //On ajoute nouveau à la liste des cases actives
                    if (indice_case_arrivee==nouveau_indice)
                    {
                        arrive=true; //Indique que l'on a atteint l'arrivée, on a alors trouvé le plus court chemin
                    }
                    else
                    {
                        bool deja_presente=false; // Indique si nouveau est déjà dans liste_case_active
                        for (int i=0; i<nb_case_active;i++)
                        {
                            if (liste_case_active[i]==nouveau_indice)
                            {
                                deja_presente=true; //Nouveau était déjà dans les points à traiter
                                while((i>1)&&(cout_total[i]<cout_total[i-1])) // On replace cet élement, le 0^ème étant le point actif, on ne le compare pas
                                {
                                    liste_case_active[i]=liste_case_active[i-1];
                                    liste_case_active[i-1]=nouveau_indice;
                                    i-=1;
                                }
                                break;
                            }
                        }
                        if (deja_presente==false) // Nouveau n'était pas dans la liste des points à traiter
                        {
                            liste_case_active[nb_case_active]=nouveau_indice; //On l'ajoute à la liste des points à traiter
                            int pos=nb_case_active;
                            nb_case_active+=1;
                            while((pos>1)&&(cout_total[liste_case_active[pos]]<cout_total[liste_case_active[pos-1]])) // On place cet element
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
        // On enleve le point que l'on vient de traiter de la liste
        nb_case_active-=1;
        for (int i=0;i<nb_case_active;i++)
        {
            liste_case_active[i]=liste_case_active[i+1];
        }

    }
    if (arrive) //On a trouvé un chemin
    {
        taille_chemin = 0; //On réinitialise la taille du chemin (utile si cette fonction a déjà été appelé pour cet ennemi)
        int indice=indice_case_arrivee;
        while(indice!=indice_case_init)
        {
            chemin_de_ennemi[taille_chemin]=indice; //On retourne les cases du chemin
            indice=predecesseur[indice]; //On remonte dans les prédecesseur pour trouver le chemin
            taille_chemin++; //On retourne la taille du chemin
        }
    }

    return arrive; //On retourne vrai si un chemin a été trouvé, faux sinon.
}
