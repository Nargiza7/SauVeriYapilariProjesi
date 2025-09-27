#ifndef CUCEGEZEGEN_H
#define CUCEGEZEGEN_H
#include "Gezegen.h"

struct CuceGezegen {
    Gezegen super;
};
typedef struct CuceGezegen CuceGezegen;

CuceGezegen* CuceGezegen_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi);
double CuceGezegen_GetYaslanmaFaktoru(const Gezegen* g);
void CuceGezegen_ToString(const Gezegen* g, char* output);
void CuceGezegen_Yoket(Gezegen* g);

#endif // CUCEGEZEGEN_H