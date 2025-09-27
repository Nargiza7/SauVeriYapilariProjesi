#ifndef DOSYAOKUMA_H
#define DOSYAOKUMA_H

#include "Gezegen.h"
#include "Kisi.h"
#include "UzayAraci.h"

// Gezegenleri oku
Gezegen *gezegenleriOku(const char *dosyaYolu, int *gezegenSayisi);

// Uzay araçlarını oku
UzayAraci *uzayAraclariniOku(const char *dosyaYolu, int *aracSayisi);

// Kisileri oku
Kisi *kisileriOku(const char *dosyaYolu, int *kisiSayisi);

void kisileriYazdir(const char *dosyaAdi);
void araclariYazdir(const char *dosyaAdi);
void gezegenleriYazdir(const char *dosyaAdi);

#endif // DOSYAOKUMA_H
