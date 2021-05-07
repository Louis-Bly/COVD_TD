#include "priorite.h"

FilePriorite::FilePriorite()
{
    PointDist a(0,0,0);
    v.push_back(a); //On met un élément à l'emplacement 0 que l'on n'utilisera pas
}

bool FilePriorite::empty() const
{
    if (v.size()==1)
    {
        return true;
    }
    return false;
}

// Ajoute un element
void FilePriorite::push(PointDist d) {
    v.push_back(d);
    int i=v.size()-1;
    bool desequilibrer=true;
    while (desequilibrer)
    {
        if ((i==1)||(v[i]<v[(i-i%2)/2]))
        {
            desequilibrer=false; //L'arbre est réparé
        }
        else
        {
            std::swap(v[i],v[(i-i%2)/2]);
            i=(i-i%2)/2;
        }
    }
}

// Retire un element
PointDist FilePriorite::pop() {
    int n=v.size()-2;
    int i=1;
    std::swap(v[1],v[n+1]);
    bool desequilibrer=true;
    while (desequilibrer)
    {
        if (2*i==n) //Une seule racine
        {
            if (v[i]<v[n])
            {
                std::swap(v[i],v[n]);
            }
            desequilibrer=false;
        }
        else //0 ou 2 racines
        {
            if ((i>(n-n%2)/2) || ( (v[2*i]<v[i]) && (v[2*i+1]<v[i])))
            {
                desequilibrer=false; //L'arbre est réparé
            }
            else
            {
                if ((v[i]<v[2*i]) && (v[2*i+1]<v[2*i]))
                {
                    std::swap(v[i],v[i*2]);
                    i=i*2;
                }
                else
                {
                    std::swap(v[i],v[i*2+1]);
                    i=i*2+1;
                }
            }
        }

    }
    PointDist a=v.back();
    v.pop_back();
    return a;
}
