
#ifndef SATIRLISTESIDUGUM_HPP
#define SATIRLISTESIDUGUM_HPP



#include <iostream>
using namespace std;

class SatirListesiDugum {
public:
    int veri;
    SatirListesiDugum *sonraki;
    SatirListesiDugum *onceki;

    SatirListesiDugum(const int veri, SatirListesiDugum *sonraki, SatirListesiDugum *onceki);
    SatirListesiDugum(const int veri, SatirListesiDugum*sonraki);
    SatirListesiDugum(const int veri);
};



#endif 

