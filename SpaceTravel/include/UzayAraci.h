#ifndef UZAY_ARACI_H
#define UZAY_ARACI_H

#include "Gezegen.h"
#include <stddef.h>
#include <stdbool.h>
typedef struct Gezegen Gezegen;
typedef struct Kisi Kisi;

struct UzayAraci
{
    char ad[50];
    char kalkisGezegeni[50];
    char varisGezegeni[50];
    char kalkisTarihi[20];
    double mesafeSaatCinsinden;
    double kalanSaat;
    char durum[20];
    char tahminiVarisTarihi[50];
    bool imhaEdildi;
    char mevutKonum;
};
typedef struct UzayAraci UzayAraci;
UzayAraci UzayAraciOlustur(const char *ad, const char *kalkisGezegeni, const char *varisGezegeni,
                           const char *kalkisTarihi, double mesafeSaatCinsinden);

// Metotlar
void durumuGuncelle(UzayAraci *uzayAraci, Gezegen *kalkisGezegen, Gezegen *varisGezegen);
void yolculukEt(UzayAraci *uzayAraci, int saat);
void ekipDurumunuKontrolEt(UzayAraci *uzayAraci, Kisi *kisiler, size_t kisiSayisi);
void ilkTahminiVarisTarihiniHesapla(UzayAraci *uzayAraci, Gezegen *kalkisGezegen, Gezegen *varisGezegen);

// Getter fonksiyonlar
const char *getMevcutKonum(UzayAraci *uzayAraci);
const char *getDurum(UzayAraci *uzayAraci);
bool varisGerceklestiMi(UzayAraci *uzayAraci);
const char *getTahminiVarisTarihi(UzayAraci *uzayAraci);
bool imhaDurumu(UzayAraci *uzayAraci);
UzayAraci *araciBul(const char *ad, UzayAraci *araclar, int aracSayisi);

#endif // UZAY_ARACI_H
