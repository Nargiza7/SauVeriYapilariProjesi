#ifndef GEZEGEN_H
#define GEZEGEN_H

#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_DATE_STRING 40

typedef struct Kisi Kisi;
typedef struct UzayAraci UzayAraci;
typedef struct Gezegen Gezegen;

typedef enum
{
    GEZEGEN_TURU_KAYAC,
    GEZEGEN_TURU_GAZ_DEVI,
    GEZEGEN_TURU_BUZ_DEVI,
    GEZEGEN_TURU_CUCE,
    GEZEGEN_TURU_BILINMIYOR
} GezegenTuru;

// Fonksiyon gösterici tiplerinin tanımları
typedef double (*getYaslanmaFaktoru_fp)(const Gezegen *);
typedef void (*gezegenToString_fp)(const Gezegen *, char *output);
typedef void (*gezegenYoket_fp)(Gezegen *); // Bellek temizliği için

struct Gezegen
{
    char gezegenAdi[50];
    int gezegenTuru;
    int gunlukSaatSayisi;
    struct tm mevcutTarih;
    int birikmisSaat;

    // Polimorfik Davranışlar için Fonksiyon Göstericileri
    getYaslanmaFaktoru_fp getYaslanmaFaktoru;
    gezegenToString_fp toString;
    gezegenYoket_fp yoket;
};

// Gezegen üst sınıfının varsayılan fonksiyon implementasyonları
double Gezegen_DefaultGetYaslanmaFaktoru(const Gezegen *g);
void Gezegen_DefaultToString(const Gezegen *g, char *output);
void Gezegen_Yoket(Gezegen *g);

void Gezegen_Init(Gezegen *g, const char *gezegenAdi, int gezegenTuru, int gunlukSaatSayisi, const char *baslangicTarihi);

void Gezegen_ZamaniIleriAl(Gezegen *g, int saat);

// Getter'lar
const char *Gezegen_GetGezegenAdi(Gezegen *g);
int Gezegen_GetGunlukSaatSayisi(Gezegen *g);
struct tm Gezegen_GetMevcutTarih(Gezegen *g);

// Tarihi yazı olarak döndürür
void Gezegen_mevcutTarihiYaziOlarakGetir(Gezegen *g, char *output);

// İki tarihi karşılaştırır
int Gezegen_TarihAyniMi(Gezegen *g, const char *digerTarihStr);

// X gün sonrası tarihi döndürür
void Gezegen_SuGunSonrasiTarih(Gezegen *g, int kacGunSonra, char *output);

// X saat sonrası tarihi döndürür
void Gezegen_SuSaatSonrasiTarih(Gezegen *g, int kacSaatSonra, char *output);

// ToString benzeri

Gezegen *gezegenBul(const char *gezegenAdi, Gezegen *gezegenler, int gezegenSayisi);

#endif // GEZEGEN_H
