// GazDevi.h
#ifndef GAZDEVI_H
#define GAZDEVI_H
#include "Gezegen.h"

struct GazDevi {
    Gezegen super;
};
typedef struct GazDevi GazDevi;

GazDevi* GazDevi_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi);
double GazDevi_GetYaslanmaFaktoru(const Gezegen* g);
void GazDevi_ToString(const Gezegen* g, char* output);
void GazDevi_Yoket(Gezegen* g);

#endif // GAZDEVI_H