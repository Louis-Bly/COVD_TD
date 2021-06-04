#include "chemin.h"

chemin::chemin()
{

}

chemin::chemin(grille G)
{
    direction= new point[G.get_nombre_case()];
    cout_des_cases=new int[G.get_nombre_case()];
}


