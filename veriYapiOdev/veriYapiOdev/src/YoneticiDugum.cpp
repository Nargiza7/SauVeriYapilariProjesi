  
#include "YoneticiDugum.hpp"


YoneticiDugum::YoneticiDugum(SatirListesi* veri, YoneticiDugum *sonraki , YoneticiDugum *onceki) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki = onceki;
    this->ort = ortHesapla();
}

YoneticiDugum::YoneticiDugum(SatirListesi* veri, YoneticiDugum *sonraki ) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki = onceki;
    this->ort = ortHesapla();
}

YoneticiDugum::YoneticiDugum(SatirListesi* veri) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki = onceki;
    this->ort = ortHesapla();
}
double YoneticiDugum::ortHesapla() {
    double total = 0;
    if (this->veri->isEmpty())
        return total;

    int count = this->veri->Count();
    for (int i = 0; i < count; ++i) {
        total += this->veri->elementAt(i);
    }
    return total / count;
}
