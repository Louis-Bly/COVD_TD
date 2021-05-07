#include "priorite.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

const int n=20;

int main() {
    std::srand((unsigned int)std::time(0));
    std::vector<PointDist> v;
    FilePriorite F;
    for(int i=0; i<n; i++)
        v.push_back( PointDist(i,0, (double)i) );
    for (int i=0; i<v.size();i++)
    {
        int j=rand()%(v.size());
        std::swap(v[i],v[j]);
    }
    for (int i=1; i<=v.size();i++)
    {
        F.push(v[i-1]);
    }
    while (F.empty()==false)
    {
        PointDist a=F.pop();
        cout<<a.i<<endl;
    }
    return 0;
}
