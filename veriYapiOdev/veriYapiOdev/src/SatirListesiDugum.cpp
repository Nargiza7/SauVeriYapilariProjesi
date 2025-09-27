
#include "SatirListesiDugum.hpp"

SatirListesiDugum::SatirListesiDugum(const int veri, SatirListesiDugum *sonraki , SatirListesiDugum *onceki ) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki= onceki;
}
SatirListesiDugum::SatirListesiDugum(const int data, SatirListesiDugum *next) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki = onceki;
}
SatirListesiDugum::SatirListesiDugum(const int data) {
    this->veri = veri;
    this->sonraki = sonraki;
    this->onceki = onceki;
}
