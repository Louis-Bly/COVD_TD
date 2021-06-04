#include "chemin.h"

chemin::chemin()
{

}

chemin::chemin(int nb_largeur_case, int nb_hauteur_case)
{
    direction= new point[nb_largeur_case*nb_hauteur_case];
}
