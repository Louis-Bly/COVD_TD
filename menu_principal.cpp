#include "menu_principal.h"

Menu::Menu()
{

}

Menu::Menu(int l, int h, int e)
{
    largeur=l;
    hauteur=h;
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
    drawString(ecart_cote+largeur*0.16,floor(hauteur/13)+2*floor(hauteur/13)+floor(hauteur/17),"N  I  V  E  A  U    1",ecriture,40);
    for (int i=2; i<5; i++)
    {
        drawString(ecart_cote+largeur*0.18,floor(hauteur/13)+2*i*floor(hauteur/13)+floor(hauteur/17),"A    V  E  N  I  R",ecriture,40);
    }
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
            // On lance le niveau 1
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
    }
    else if (ecran_actif=="regle")
        if ((x>ecart_cote)&&(x<largeur-ecart_cote)&&(y>11*floor(hauteur/13))&&(y<12*floor(hauteur/13)))
        {
            ecran_actif="info";
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
