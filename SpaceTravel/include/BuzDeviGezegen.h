#ifndef BUZDEVI_H
#define BUZDEVI_H
#include "Gezegen.h"

struct BuzDevi {
    Gezegen super;
};
typedef struct BuzDevi BuzDevi;

BuzDevi* BuzDevi_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi);
double BuzDevi_GetYaslanmaFaktoru(const Gezegen* g);
void BuzDevi_ToString(const Gezegen* g, char* output);
void BuzDevi_Yoket(Gezegen* g);

#endif // BUZDEVI_H