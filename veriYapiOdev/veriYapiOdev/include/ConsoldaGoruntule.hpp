#ifndef CONSOLDAGORUNTULE_HPP
#define CONSOLDAGORUNTULE_HPP

#include "YoneticiListesi.hpp"
#include "ConsolePosition.hpp"


#define BirSayfadaGoster 8
#define BaslaOffset 0

enum Yon {
    ust = 0,
    alt = 1,
    yenile = 2,

};

enum SayfaYonu{
    ustSayfa = 0,
    altSayfa = 1,
};

class ConsoldaGoruntule {
private:
    YoneticiListesi *yonetici;
    int durum;
    int baslaOffset;
    int sonOffset;

    void setOffsets();
public:

    void setDurum(Yon dr);
    void SetSayfa(SayfaYonu sy);


    ConsoldaGoruntule(YoneticiListesi* yonetici);

    void yazdirYoneticiListesi();

    void yazdirSelectedSatirListesi(int x, int y);

    int RastgeleSelectedDugumGoruntule()throw (IndexOutOfBounds, NoSuchElement);

    void YoneticiDugumSil();

    void RastgeleSelectedDugumSil(int rastgeleIndex)throw (IndexOutOfBounds, NoSuchElement);
};

#endif 

