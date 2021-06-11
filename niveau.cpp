#include "niveau.h"

ennemi* liste_ennemis;
tour* liste_tours;
projectile* liste_projectiles;

bool tutoriel(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{

    init_random();
    //Un seul ennemi de chaque type
    int nb_ennemi_basique=1;
    int nb_ennemi_ameliore=1;
    int nb_ennemi_rapide=1;
    int nb_ennemi_tank=1;
    bool tutoriel=true; //Tous les ennemis apparaissent l'un après l'autre, à un rythme lent
    int indice_arrivee=0;
    int ecart=100; //Pas utile dans le tutoriel, utile seulement dans les autres niveaux
    int argent=1000; //Le joueur peut placer beaucoup de tours
    return niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart, argent, indice_arrivee, tutoriel);

}

bool niveau1(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    //On définit les nombres d'ennemis, un écart moyen, l'argent initial et l'arrivée
    int nb_ennemi_basique=50;
    int nb_ennemi_ameliore=20;
    int nb_ennemi_rapide=20;
    int nb_ennemi_tank=10;
    int ecart_moyen=25;
    int argent=200;
    int indice_arrivee=0;
    return niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

bool niveau2(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    int nb_ennemi_basique=30;
    int nb_ennemi_ameliore=60;
    int nb_ennemi_rapide=5;
    int nb_ennemi_tank=20;
    int ecart_moyen=20;
    int argent=200;
    int indice_arrivee=50;
    return niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

bool niveau3(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    init_random();
    int nb_ennemi_basique=100;
    int nb_ennemi_ameliore=10;
    int nb_ennemi_rapide=60;
    int nb_ennemi_tank=10;
    int ecart_moyen=26;
    int argent=200;
    int indice_arrivee=250;
    return niveau(largeur_fenetre, hauteur_fenetre, taille_case, nb_ennemi_basique, nb_ennemi_ameliore, nb_ennemi_rapide, nb_ennemi_tank, ecart_moyen, argent, indice_arrivee);
}

int choix_arrivee(int largeur_fenetre, int hauteur_fenetre, int taille_case, grille g, int marge)
{
    g.affiche();
    drawString(4*marge,hauteur_fenetre-marge/2,"Choix du point d'arrivée",BLACK,20);
    point arrivee;
    bool arrivee_sur_ecran=false;
    while (not arrivee_sur_ecran) //Tant que le point n'est pas valide
    {
        getMouse(arrivee.x,arrivee.y);
        arrivee_sur_ecran=((arrivee.x>0)&&(arrivee.x<g.get_taille_case()*(g.get_nb_largeur_case()-1))&&(arrivee.y>0)&&(arrivee.y<g.get_taille_case()*g.get_nb_hauteur_case()));
    }
    return g.get_place(arrivee);
}

bool edition_de_niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case)
{
    int marge=160;

    //Choix du point d'arrivée
    grille g(largeur_fenetre,hauteur_fenetre-marge,taille_case);
    int arrivee_indice=choix_arrivee(largeur_fenetre,hauteur_fenetre,taille_case,g, marge);
    point arrivee=g.get_pos(arrivee_indice);
    fillRect(arrivee.x,arrivee.y,g.get_taille_case(),g.get_taille_case(),CYAN);
    click();


    //Choix des ennemis
    fillRect(0,0,largeur_fenetre,hauteur_fenetre,WHITE);
    int taille_mini_case=100;
    int ecart_bord=largeur_fenetre*0.45;
    int ecart=50;
    for (int i=1; i<6; i++)//Dessine les cases pour choisir le nombre d'ennemis
    {
        if (i!=5)
        {
            for (int j=0; j<3;j++)
            {
                fillRect(ecart_bord+j*(ecart+taille_mini_case),floor(hauteur_fenetre/13)+i*2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+j*(ecart+taille_mini_case),floor(hauteur_fenetre/13)+i*2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
            }
            drawRect(ecart_bord+floor(taille_mini_case/4),floor(hauteur_fenetre/13)+i*2*floor(hauteur_fenetre/13)+floor(taille_mini_case/2),floor(taille_mini_case/2),0,YELLOW,10);
            drawRect(ecart_bord+floor(taille_mini_case/4)+2*(ecart+taille_mini_case),floor(hauteur_fenetre/13)+i*2*floor(hauteur_fenetre/13)+floor(taille_mini_case/2),floor(taille_mini_case/2),0,YELLOW,10);

            drawRect(ecart_bord+floor(taille_mini_case/2)+2*(ecart+taille_mini_case),floor(hauteur_fenetre/13)+i*2*floor(hauteur_fenetre/13)+floor(taille_mini_case/4),0,floor(taille_mini_case/2),YELLOW,10);

        }
    }

    //Dessine les cases retour et Choix des ennemis
    fillRect(ecart_bord-(ecart+taille_mini_case),floor(hauteur_fenetre/13)+5*2*floor(hauteur_fenetre/13),taille_mini_case+3*(ecart+taille_mini_case),taille_mini_case, BLUE);
    drawRect(ecart_bord-(ecart+taille_mini_case),floor(hauteur_fenetre/13)+5*2*floor(hauteur_fenetre/13),taille_mini_case+3*(ecart+taille_mini_case),taille_mini_case, BLACK,10);

    drawString(ecart_bord+taille_mini_case-(ecart+taille_mini_case),floor(hauteur_fenetre/13)+5*2*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),"J  O  U  E  R",YELLOW,40);

    drawString(ecart_bord-floor(1.5*(ecart+taille_mini_case)),floor(hauteur_fenetre/9),"CHOIX DU NOMBRE D'ENNEMIS", RED,40);


    //On s'occupe de demander le nombre d'ennemis de chaque type
    point emplacement;
    emplacement.x=ecart_bord*0.9;
    emplacement.y=floor(hauteur_fenetre/13)+2*floor(hauteur_fenetre/13)+floor(1.2*ecart);
    ennemi E= ennemi_basique(emplacement,g);
    E.Affiche_ennemi(); E.Affiche_barre_vie();
    int nb_basique=20; //l'utilisateur sera amené à changer cette valeur
    drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),3*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_basique),YELLOW,40);


    emplacement.y=floor(hauteur_fenetre/13)+4*floor(hauteur_fenetre/13)+floor(1.2*ecart);
    ennemi E2= ennemi_ameliore(emplacement,g);
    E2.Affiche_ennemi(); E2.Affiche_barre_vie();
    int nb_ameliore=15;//l'utilisateur sera amené à changer cette valeur
    drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),5*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_ameliore),YELLOW,40);


    emplacement.y=floor(hauteur_fenetre/13)+6*floor(hauteur_fenetre/13)+floor(1.2*ecart);
    ennemi E3= ennemi_rapide(emplacement,g);
    E3.Affiche_ennemi(); E3.Affiche_barre_vie();
    int nb_rapide=10;//l'utilisateur sera amené à changer cette valeur
    drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),7*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_rapide),YELLOW,40);



    emplacement.y=floor(hauteur_fenetre/13)+8*floor(hauteur_fenetre/13)+floor(1.2*ecart);
    ennemi E4= ennemi_tank(emplacement,g);
    E4.Affiche_ennemi(); E4.Affiche_barre_vie();
    int nb_tank=5;//l'utilisateur sera amené à changer cette valeur
    drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),9*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_tank),YELLOW,40);


    bool demarrer=false;
    while (not demarrer)
    {
        int x; int y;
        getMouse(x,y);
        if ((x>ecart_bord)&&(x<ecart_bord+taille_mini_case)) //Concerne les moins
        {
            if ((y>3*floor(hauteur_fenetre/13))&&(y<4*floor(hauteur_fenetre/13))) //Ennemi basique
            {
                if (nb_basique>0)
                    nb_basique--;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),3*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_basique),YELLOW,40);
            }
            else if ((y>5*floor(hauteur_fenetre/13))&&(y<6*floor(hauteur_fenetre/13))) //Ennemi ameliore
            {

                    nb_ameliore--;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+4*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+4*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),5*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_ameliore),YELLOW,40);
            }
            else if ((y>7*floor(hauteur_fenetre/13))&&(y<8*floor(hauteur_fenetre/13))) //Ennemi rapide
            {
                if (nb_rapide>0)
                    nb_rapide--;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+6*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+6*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),7*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_rapide),YELLOW,40);
            }
            else if ((y>9*floor(hauteur_fenetre/13))&&(y<10*floor(hauteur_fenetre/13))) //Ennemi tank
            {
                if (nb_tank>0)
                    nb_tank--;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+8*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+8*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),9*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_tank),YELLOW,40);
            }
        }
        else if ((x>ecart_bord+2*(taille_mini_case+ecart))&&(x<ecart_bord+taille_mini_case+2*(taille_mini_case+ecart))) //Concerne les plus
        {
            if ((y>3*floor(hauteur_fenetre/13))&&(y<4*floor(hauteur_fenetre/13))) //Ennemi basique
            {
                nb_basique++;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+2*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),3*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_basique),YELLOW,40);
            }
            else if ((y>5*floor(hauteur_fenetre/13))&&(y<6*floor(hauteur_fenetre/13)))// Ennemi ameliore
            {
                nb_ameliore++;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+4*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+4*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),5*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_ameliore),YELLOW,40);
            }
            else if ((y>7*floor(hauteur_fenetre/13))&&(y<8*floor(hauteur_fenetre/13)))//Ennemi rapide
            {
                nb_rapide++;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+6*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+6*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),7*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_rapide),YELLOW,40);
            }
            else if ((y>9*floor(hauteur_fenetre/13))&&(y<10*floor(hauteur_fenetre/13))) //Ennemi tank
            {
                nb_tank++;
                fillRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+8*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLUE);
                drawRect(ecart_bord+(ecart+taille_mini_case),floor(hauteur_fenetre/13)+8*floor(hauteur_fenetre/13),taille_mini_case,taille_mini_case, BLACK,10);
                drawString(ecart_bord+1*(ecart+taille_mini_case)+floor(taille_mini_case/4),9*floor(hauteur_fenetre/13)+floor(taille_mini_case*0.75),std::to_string(nb_tank),YELLOW,40);
            }
        }
        else if ((x>ecart_bord)&&(x<ecart_bord+taille_mini_case+2*(taille_mini_case+ecart))) //Clique sur jouer
        {
            if ((y>11*floor(hauteur_fenetre/13))&&(y<12*floor(hauteur_fenetre/13)))
            {
                demarrer=true;
            }
        }
    }
    int argent_init=4*nb_tank+3*nb_rapide+2*nb_ameliore+nb_basique+5; //Le +5 permet de toujours pouvoir placer au moins une tour



    fillRect(0,0,largeur_fenetre,hauteur_fenetre,WHITE);
    return niveau(largeur_fenetre,hauteur_fenetre,taille_case,nb_basique,nb_ameliore,nb_rapide,nb_tank,25,argent_init, arrivee_indice);


}


//Fonction appelé lors du déroulement d'un niveau/Tutoriel
bool niveau(int largeur_fenetre, int hauteur_fenetre, int taille_case, int nb_basique, int nb_ameliore, int nb_rapide, int nb_tank, int ecart_moyen, int argent_initial, int indice_arrivee, bool tutoriel)
{

    int buffer_tour=-1;
    const int taille_marge = 160; //Espace inférieur (ajout/vente de tour, affichage de l'argent...)
    int nb_ennemis=nb_ameliore+nb_basique+nb_rapide+nb_tank; //Nombre d'ennemis total

    //On définit les différents outils du jeu
    interface Interface=interface(nb_ennemis,largeur_fenetre,hauteur_fenetre,taille_marge,120,200,70, argent_initial);

    liste_ennemis = new ennemi[nb_ennemis];
    grille g(largeur_fenetre,hauteur_fenetre-taille_marge,taille_case);

    liste_tours = new tour [g.get_nombre_case()]; //g.get_nombre_case après le merge
    liste_projectiles = new projectile [g.get_nombre_case()]; //g.get_nombre_case après le merge
    point a = g.get_indices_xy(indice_arrivee); // Définition du point arrivée (ligne/colonne)

    //Définition des positions de départ des ennemis

    point position_origine_b;
    point position_origine_r;
    point position_origine_a;
    point position_origine_t;

    for (int i=0; i<nb_basique;i++)
    {
        if(tutoriel)
        {
            //Position fixe
            position_origine_b.x=Interface.get_largeur()+500;
            position_origine_b.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            //Position aléatoire
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_b.x=Interface.get_largeur()+c*5;
            position_origine_b.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_basique(position_origine_b, g); //Ajout des ennemis basiques à la liste
    }
    //On fait de même pour les autres types d'ennemis
    for (int i=nb_basique; i<nb_basique+nb_ameliore;i++)
    {
        if(tutoriel)
        {
            position_origine_a.x=Interface.get_largeur()+100;
            position_origine_a.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_a.x=Interface.get_largeur()+c*6;
            position_origine_a.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_ameliore(position_origine_a, g);
    }
    for (int i=nb_basique+nb_ameliore; i<nb_basique+nb_ameliore+nb_rapide;i++)
    {
        if(tutoriel)
        {
            position_origine_r.x=Interface.get_largeur()+2500;
            position_origine_r.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_r.x=Interface.get_largeur()+c*10;
            position_origine_r.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_rapide(position_origine_r, g);
    }
    for (int i=nb_basique+nb_ameliore+nb_rapide; i<nb_ennemis;i++)
    {
        if(tutoriel)
        {
            position_origine_t.x=Interface.get_largeur()+400;
            position_origine_t.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        else
        {
            int c=rand()%(20*nb_ennemis);
            c=ecart_moyen*sqrt(c); // Les ennemis ont plus de chance d'arrivée de loin
            position_origine_t.x=Interface.get_largeur()+c*2;
            position_origine_t.y=floor(taille_case/2)+taille_case*(rand()%10);
        }
        liste_ennemis[i]=ennemi_tank(position_origine_t, g);
    }


    g.affiche_arrivee(indice_arrivee);
    Interface.Affiche_marge();
    Interface.Affiche_nb_ennemi_restant();
    Interface.Affiche_argent();
    for(int i=0;i<6;i++)
    {
        int j =i;
        Interface.Affiche_case_tour(j,g);
    }

    for (int i=0; i<Interface.get_nb_ennemi(); i++)
    {
        liste_ennemis[i].Affiche_ennemi();
        liste_ennemis[i].Affiche_barre_vie();

    }
    bool perdu = false;
    bool fini = false;
    while (not fini) //Boucle principale
    {
        g.affiche_arrivee(indice_arrivee);
        Interface.Affiche_marge();
        Interface.Affiche_nb_ennemi_restant();
        for(int i=0; i<Interface.get_nb_proj();i++){
            liste_projectiles[i].efface();
        }
        g.affiche();
        for(int i=0; i<Interface.get_nb_tour(); i++){
            liste_tours[i].affiche(g);
            int nbproj = Interface.get_nb_proj();
            liste_tours[i].tire(Interface.get_nb_ennemi(),nbproj,g.get_taille_case(),liste_ennemis,liste_projectiles);
            Interface.set_nb_proj(nbproj);
        }
        for (int i=0; i<Interface.get_nb_ennemi(); i++)
        {
            Interface.Affiche_argent();
            for (int n=0;n<5;n++)
            {
                Interface.dessine_argent_suffisant(cout_tour[n],n);
            }
            liste_ennemis[i].Deplace(g,a); //Les ennemis se déplacent

            //TEST
            int ar=0;
            int k=Interface.get_nb_ennemi();
            if ((liste_ennemis[i].get_case_actuelle().x==a.x)&&(liste_ennemis[i].get_case_actuelle().y==a.y))
            {
                liste_ennemis[i].Perte_vie(liste_ennemis[i].get_hp(), ar, i, k, liste_ennemis);

                Interface.Affiche_nb_ennemi_restant();
                Interface.set_nb_ennemi(k);
                perdu = true;
            }
            if (liste_ennemis[i].get_dans_le_cadre())
            {
                liste_ennemis[i].Chemin_ennemi.Calcul_plus_court_chemin(g.get_indices_xy(g.get_place(liste_ennemis[i].get_position())),g,a);
            }
            //TEST

        }
        for(int i=0; i<Interface.get_nb_proj();i++){
            liste_projectiles[i].deplace();
            int nb_proj = Interface.get_nb_proj();
            int nb_ennemi = Interface.get_nb_ennemi();
            int argent_act = Interface.get_Argent();
            liste_projectiles[i].collision(i, liste_projectiles, liste_ennemis, nb_proj, nb_ennemi, largeur_fenetre, hauteur_fenetre-taille_marge-10, argent_act);
            Interface.set_nb_proj(nb_proj);
            Interface.set_nb_ennemi(nb_ennemi);
            Interface.set_Argent(argent_act);
        }
        Interface.choisir_tour(buffer_tour,liste_tours, g, liste_ennemis, a);

        fini = Interface.get_nb_ennemi()==0 or perdu;

        milliSleep(100);
    }
    return not perdu;
}
