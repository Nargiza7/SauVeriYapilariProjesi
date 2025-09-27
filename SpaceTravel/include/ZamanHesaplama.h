#ifndef ZAMANHESAPLAMA_H
#define ZAMANHESAPLAMA_H
#include <time.h>

int parseTarih(const char *tarihStr, struct tm *outDate);

int tarihFarkiSaatOlarak(const char *baslangicTarihi, const char *bitisTarihi, int gunlukSaatSayisi);

char *varisTarihiniHesapla(const char *kalkisTarihi, int kalkisGunlukSaat, double mesafeSaatCinsinden, int varisGunlukSaat, const char *varisMevcutTarih);

char *tamYolculukTarihiniHesapla(const char *kalkisMevcutTarih, const char *uzayAraciKalkisTarihi, int kalkisGunlukSaat, double mesafeSaatCinsinden, const char *varisMevcutTarih, int varisGunlukSaat);

#endif
