#include "menu_principal.h"

Menu::Menu()
{

}

Menu::Menu(int l, int h, int e, int t_tour)
{
    largeur=l;
    hauteur=h;
    taille_tour=t_tour;
    ecriture=YELLOW;
    remplissage=BLUE;
    titre=RED;
    ecart_cote=e;
    ecran_actif="principal";
}

void Menu::efface_ecran()
{
    fillRect(0,0,largeur,hauteur,WHITE);
}

void Menu::Menu_principal()
{
    openWindow(largeur, hauteur);
    draw_boutons_ecran_acceuil();
    while (ecran_actif!="Quitter")
    {
        changement_de_page();
        affichage();
    }
}

void Menu::affichage()
{
    efface_ecran();
    if (ecran_actif=="principal")
    {
        draw_boutons_ecran_acceuil();
    }
    else if (ecran_actif=="jeu")
    {
        draw_boutons_ecran_jouer();
    }
    else if (ecran_actif=="info")
    {
        draw_boutons_ecran_info();
    }
    else if (ecran_actif=="regle")
    {
        regle();
    }
    else if (ecran_actif=="info ennemis")
    {
        Info_ennemi();
    }
    else if (ecran_actif=="info tours")
    {
        Info_tour();
    }
}

void Menu::draw_boutons_ecran_acceuil()
{
    for (int i=0; i<3; i++)
    {
        fillRect(ecart_cote,floor(hauteur/2)+i*2*floor(hauteur/12),largeur-2*ecart_cote, floor(hauteur/12), remplissage);
        drawRect(ecart_cote,floor(hauteur/2)+i*2*floor(hauteur/12),largeur-2*ecart_cote, floor(hauteur/12), BLACK,10);


    }
    drawString(ecart_cote+largeur*0.2,floor(hauteur/2)+floor(hauteur/17),"J  O  U  E  R",ecriture,40);
    drawString(ecart_cote+largeur*0.1,floor(hauteur/2)+2*floor(hauteur/12)+floor(hauteur/17),"C O M M E N T   J O U E R",ecriture,40);
    drawString(ecart_cote+largeur*0.16,floor(hauteur/2)+floor(hauteur/17)+4*floor(hauteur/12),"Q  U  I  T  T  E  R",ecriture,40);
}


void Menu::draw_boutons_ecran_jouer()
{
    for (int i=0; i<6; i++)
    {
        fillRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), remplissage);
        drawRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), BLACK,10);
    }
    drawString(ecart_cote+largeur*0.2,floor(hauteur/13)+floor(hauteur/17),"J  O  U  E  R",titre,40);
    drawString(ecart_cote+largeur*0.16,floor(hauteur/13)+2*floor(hauteur/13)+floor(hauteur/17),"T  U  T  O  R  I  E  L",ecriture,40);
    drawString(ecart_cote+largeur*0.2,floor(hauteur/13)+4*floor(hauteur/13)+floor(hauteur/17),"N I V E A U   1",ecriture,40);
    drawString(ecart_cote+largeur*0.2,floor(hauteur/13)+6*floor(hauteur/13)+floor(hauteur/17),"N I V E A U   2",ecriture,40);
    drawString(ecart_cote+largeur*0.2,floor(hauteur/13)+8*floor(hauteur/13)+floor(hauteur/17),"N I V E A U   3",ecriture,40);

    drawString(ecart_cote+largeur*0.19,floor(hauteur/13)+floor(hauteur/17)+10*floor(hauteur/13),"R  E  T  O  U  R",ecriture,40);
}

void Menu::changement_de_page()
{
    int x,y;
    getMouse(x,y);
    if (ecran_actif=="principal")
    {

        if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>floor(hauteur/2))&&(y<floor(hauteur/12)+floor(hauteur/2)))
        {
            ecran_actif="jeu";
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>floor(hauteur/2)+2*floor(hauteur/12))&&(y<3*floor(hauteur/12)+floor(hauteur/2)))
        {
            ecran_actif="info";
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>floor(hauteur/2)+4*floor(hauteur/12))&&(y<5*floor(hauteur/12)+floor(hauteur/2)))
        {
            ecran_actif="Quitter";
        }
    }
    else if (ecran_actif=="jeu")
    {
        if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>3*floor(hauteur/13))&&(y<4*floor(hauteur/13)))
        {
            efface_ecran();
            tutoriel(largeur,hauteur,taille_tour);
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>5*floor(hauteur/13))&&(y<6*floor(hauteur/13)))
        {
            efface_ecran();
            niveau1(largeur,hauteur,taille_tour);
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>7*floor(hauteur/13))&&(y<8*floor(hauteur/13)))
        {
            efface_ecran();
            niveau2(largeur,hauteur,taille_tour);
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>9*floor(hauteur/13))&&(y<10*floor(hauteur/13)))
        {
            efface_ecran();
            niveau3(largeur,hauteur,taille_tour);
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>11*floor(hauteur/13))&&(y<12*floor(hauteur/13)))
        {
            ecran_actif="principal";
        }
    }
    else if (ecran_actif=="info")
    {
        if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>9*floor(hauteur/11))&&(y<10*floor(hauteur/11)))
        {
            ecran_actif="principal";
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>3*floor(hauteur/11))&&(y<4*floor(hauteur/11)))
        {
            ecran_actif="regle";
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>5*floor(hauteur/11))&&(y<6*floor(hauteur/11)))
        {
            ecran_actif="info ennemis";
        }
        else if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>7*floor(hauteur/11))&&(y<8*floor(hauteur/11)))
        {
            ecran_actif="info tours";
        }
    }
    else if ((ecran_actif=="regle")||(ecran_actif=="info ennemis")||(ecran_actif=="info tours"))
    {
        if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>11*floor(hauteur/13))&&(y<12*floor(hauteur/13)))
        {
            ecran_actif="info";
        }
    }
}

void Menu::draw_boutons_ecran_info()
{
    for (int i=0;i<5;i++)
    {
        fillRect(ecart_cote,floor(hauteur/11)+i*2*floor(hauteur/11),largeur-2*ecart_cote, floor(hauteur/11), remplissage);
        drawRect(ecart_cote,floor(hauteur/11)+i*2*floor(hauteur/11),largeur-2*ecart_cote, floor(hauteur/11), BLACK,10);
    }

    drawString(ecart_cote+largeur*0.12,floor(hauteur/11)+floor(hauteur/15),"C O M M E N T   J O U E R",titre,40);
    drawString(ecart_cote+largeur*0.14,3*floor(hauteur/11)+floor(hauteur/15),"R E G L E   D U   J E U",ecriture,40);
    drawString(ecart_cote+largeur*0.16,5*floor(hauteur/11)+floor(hauteur/15),"I N F O   E N N E M I S",ecriture,40);
    drawString(ecart_cote+largeur*0.18,7*floor(hauteur/11)+floor(hauteur/15),"I N F O   T O U R S",ecriture,40);
    drawString(ecart_cote+largeur*0.20,9*floor(hauteur/11)+floor(hauteur/15),"R  E  T  O  U  R",ecriture,40);
}

void Menu::regle()
{
    for (int i=0; i<6; i+=5)
    {
        fillRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), remplissage);
        drawRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), BLACK,10);
    }
    drawString(ecart_cote+largeur*0.16,floor(hauteur/12)+floor(hauteur/17),"R E G L E  D U   J E U",titre,40);
    drawString(ecart_cote+largeur*0.19,floor(hauteur/13)+floor(hauteur/17)+10*floor(hauteur/13),"R  E  T  O  U  R",ecriture,40);

    fillRect(ecart_cote,floor(hauteur/13)+2*floor(hauteur/13),largeur-2*ecart_cote, 7*floor(hauteur/13), WHITE);
    drawRect(ecart_cote,floor(hauteur/13)+2*floor(hauteur/13),largeur-2*ecart_cote, 7*floor(hauteur/13), BLACK);
    drawString(ecart_cote+largeur*0.05,3*floor(hauteur/13)+floor(hauteur/26),"Dans ce jeu, votre but est d'empêcher les ennemis d'atteindre leur objectif (case(s) avec les flèches)", BLACK );
    drawString(ecart_cote+largeur*0.05,4*floor(hauteur/13)+floor(hauteur/26),"Pour y parvenir, vous pouvez poser des tours qui tireront sur les ennemis." , BLACK);
    drawString(ecart_cote+largeur*0.05,5*floor(hauteur/13)+floor(hauteur/26),"Pour poser une tour, sélectionnez là puis placer la sur le terrain, si vous avez assez d'argent pour l'acheter", BLACK );
    drawString(ecart_cote+largeur*0.05,6*floor(hauteur/13)+floor(hauteur/26),"Faites attention, les ennemis adaptent leur trajectoire à chaque fois que vous posez une tour,", BLACK );
    drawString(ecart_cote+largeur*0.05,7*floor(hauteur/13)+floor(hauteur/26),"Par ailleurs, il vous ait impossible de leur barer totalement la route en posant des tours,", BLACK );
    drawString(ecart_cote+largeur*0.05,8*floor(hauteur/13)+floor(hauteur/26),"En effet, vous êtes contraint de toujours leur laisser un chemin disponible.", BLACK );
    drawString(ecart_cote+largeur*0.26,9*floor(hauteur/13)+floor(hauteur/26),"Bonne chance.", BLACK );
}

void Menu::Info_ennemi()
{
    for (int i=0; i<6; i+=5)
    {
        fillRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), remplissage);
        drawRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), BLACK,10);
    }
    drawString(ecart_cote+largeur*0.16,floor(hauteur/12)+floor(hauteur/17),"I N F O   E N N E M I S",titre,40);
    drawString(ecart_cote+largeur*0.19,floor(hauteur/13)+floor(hauteur/17)+10*floor(hauteur/13),"R  E  T  O  U  R",ecriture,40);

    //On définit un ennemi pour l'affichage:
    grille g(largeur,hauteur, taille_tour);
    point emplacement;
    emplacement.x=ecart_cote;
    emplacement.y=3*floor(hauteur/13);
    ennemi E= ennemi_basique(emplacement,g);
    E.Affiche_ennemi(); E.Affiche_barre_vie();
    drawString(emplacement.x+2*E.get_rayon(), emplacement.y, "L'ennemi le plus courant, il ne possède aucune compétance particulière", BLACK,20);

    emplacement.y=5*floor(hauteur/13);
    ennemi E2= ennemi_ameliore(emplacement,g);
    E2.Affiche_ennemi(); E2.Affiche_barre_vie();
    drawString(emplacement.x+2*E2.get_rayon(), emplacement.y, "Il est légèrement plus rapide et résistant que les autres", BLACK,20);

    emplacement.y=7*floor(hauteur/13);
    ennemi E3= ennemi_rapide(emplacement,g);
    E3.Affiche_ennemi(); E3.Affiche_barre_vie();
    drawString(emplacement.x+2*E3.get_rayon(), emplacement.y, "L'ennemi le plus rapide, même s'il n'est pas très résistant", BLACK,20);

    emplacement.y=9*floor(hauteur/13);
    ennemi E4= ennemi_tank(emplacement,g);
    E4.Affiche_ennemi(); E4.Affiche_barre_vie();
    drawString(emplacement.x+2*E4.get_rayon(), emplacement.y, "L'ennemi le plus résistant, cependant, il est très lent", BLACK,20);
}

void Menu::Info_tour()
{
    for (int i=0; i<6; i+=5)
    {
        fillRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), remplissage);
        drawRect(ecart_cote,floor(hauteur/13)+i*2*floor(hauteur/13),largeur-2*ecart_cote, floor(hauteur/13), BLACK,10);
    }
    drawString(ecart_cote+largeur*0.18,floor(hauteur/12)+floor(hauteur/17),"I N F O   T O U R S",titre,40);
    drawString(ecart_cote+largeur*0.19,floor(hauteur/13)+floor(hauteur/17)+10*floor(hauteur/13),"R  E  T  O  U  R",ecriture,40);

    fillRect(ecart_cote,3*floor(hauteur/13),taille_tour,taille_tour,ORANGE);
    drawString(ecart_cote+largeur*0.05,3*floor(hauteur/13)+floor(taille_tour/2),"Un simple mur, dévie les ennemis", BLACK,20);

    fillRect(ecart_cote,6*floor(hauteur/13),taille_tour,taille_tour,RED);
    drawString(ecart_cote+largeur*0.05,6*floor(hauteur/13)+floor(taille_tour/2),"Une tour basique", BLACK,20);

    fillRect(ecart_cote,9*floor(hauteur/13),taille_tour,taille_tour,BLUE);
    drawString(ecart_cote+largeur*0.05,9*floor(hauteur/13)+floor(taille_tour/2),"Une tour à petite portée mais dégats élevés", BLACK,20);

    fillRect(ecart_cote+largeur*0.32,floor(4.5*hauteur/13),taille_tour,taille_tour,GREEN);
    drawString(ecart_cote+largeur*0.37,floor(4.5*hauteur/13)+floor(taille_tour/2),"Une tour dont les flèches ne s'arrête jamais", BLACK,20);

    fillRect(ecart_cote+largeur*0.32,floor(7.5*hauteur/13),taille_tour,taille_tour,BLACK);
    drawString(ecart_cote+largeur*0.37,floor(7.5*hauteur/13)+floor(taille_tour/2),"Une tour dont les flèches explosent", BLACK,20);
}
