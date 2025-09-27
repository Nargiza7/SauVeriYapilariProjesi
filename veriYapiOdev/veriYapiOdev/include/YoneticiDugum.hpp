#ifndef YONETICIDUGUM_HPP
#define YONETICIDUGUM_HPP


#include "SatirListesi.hpp"

class YoneticiDugum {
public:
    SatirListesi* veri;
    double ort;
    YoneticiDugum *sonraki;
    YoneticiDugum *onceki;
    

    YoneticiDugum(SatirListesi* veri, YoneticiDugum *sonraki, YoneticiDugum *onceki);
    YoneticiDugum(SatirListesi* veri, YoneticiDugum *sonraki);
    YoneticiDugum(SatirListesi* veri);
    double ortHesapla();
};


#endif 

