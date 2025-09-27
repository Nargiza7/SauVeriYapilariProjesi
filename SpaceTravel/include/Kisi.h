#ifndef KISI_H
#define KISI_H
#include <stdbool.h>
#include "UzayAraci.h"
#include "Gezegen.h"

typedef struct UzayAraci UzayAraci;
typedef struct Gezegen Gezegen;

struct Kisi
{
    char isim[50];
    int yas;
    int kalanOmur;
    int hayattaMi;
    char uzayAraci[100];
};

typedef struct Kisi Kisi;

void Kisi_Init(Kisi *k, const char *isim, int yas, int kalanOmur, const char *uzayAraci);

void zamanGecir(Kisi *kisi, int saat, UzayAraci *araclar, int aracSayisi, Gezegen *gezegenler, int gezegenSayisi);

const char *getIsim(Kisi *kisi);
int getYas(Kisi *kisi);
int getKalanOmur(Kisi *kisi);
const char *getUzayAraciAdi(Kisi *kisi);
int isHayattaMi(Kisi *kisi);

#endif // KISI_H
