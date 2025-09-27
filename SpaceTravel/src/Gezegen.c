/**
 *
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 * @since 15.05.2025
 * <p>
 *  Gezegen
 * </p>
 */
#include "Gezegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DATE_STRING 40

static int parseTarih(const char *tarihStr, struct tm *outDate)
{

    if (tarihStr == NULL)
    {
        return 0;
    }

    memset(outDate, 0, sizeof(struct tm));
    int day, month, year;
    int result = sscanf(tarihStr, "%d.%d.%d", &day, &month, &year);

    if (result == 3)
    {
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1)
        {

            return 0;
        }

        outDate->tm_mday = day;
        outDate->tm_mon = month - 1;
        outDate->tm_year = year - 1900;
        return 1;
    }
}

void Gezegen_Init(Gezegen *g, const char *gezegenAdi, int gezegenTuru, int gunlukSaatSayisi, const char *baslangicTarihi)
{
    strncpy(g->gezegenAdi, gezegenAdi, sizeof(g->gezegenAdi) - 1);
    g->gezegenAdi[sizeof(g->gezegenAdi) - 1] = '\0';
    g->gezegenTuru = gezegenTuru;
    g->gunlukSaatSayisi = gunlukSaatSayisi;
    g->birikmisSaat = 0;

    if (!parseTarih(baslangicTarihi, &(g->mevcutTarih)))
    {

        printf("Gezegen: %s, Saat: %d, Tarih: %02d.%02d.%04d\n",
               g->gezegenAdi,
               g->gezegenTuru,
               g->gunlukSaatSayisi,
               g->mevcutTarih.tm_mday,
               g->mevcutTarih.tm_mon + 1,
               g->mevcutTarih.tm_year + 1900);
        printf("Gezegen: %s | Saat: %d | Tarih: %02d.%02d.%d\n",
               g->gezegenAdi, g->gezegenTuru, g->gunlukSaatSayisi,
               g->mevcutTarih.tm_mday, g->mevcutTarih.tm_mon + 1, g->mevcutTarih.tm_year + 1900);
    }
    g->getYaslanmaFaktoru = &Gezegen_DefaultGetYaslanmaFaktoru;
    g->toString = &Gezegen_DefaultToString;
    g->yoket = &Gezegen_Yoket;
}

// Gezegen üst sınıfının varsayılan yaşlanma faktörü implementasyonu (alt sınıflar override edecek)
double Gezegen_DefaultGetYaslanmaFaktoru(const Gezegen *g)
{
    switch (g->gezegenTuru)
    {
    case GEZEGEN_TURU_KAYAC:
        return 1.0;
    case GEZEGEN_TURU_GAZ_DEVI:
        return 0.1;
    case GEZEGEN_TURU_BUZ_DEVI:
        return 0.5;
    case GEZEGEN_TURU_CUCE:
        return 0.01;
    default:
        return 1.0;
    }
}

void Gezegen_DefaultToString(const Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir((Gezegen *)g, tarihStr);
    snprintf(output, 200, "--- Gezegen: %s --- Tur: %d, Gunluk Saat: %d, Mevcut Tarih: %s, Yaslanma Faktoru: %.2lf",
             g->gezegenAdi, g->gezegenTuru, g->gunlukSaatSayisi, tarihStr, g->getYaslanmaFaktoru(g));
}

// Gezegen üst sınıfının yoket implementasyonu (eğer dinamik bellek tahsisi varsa)
void Gezegen_Yoket(Gezegen *g)
{
    if (g == NULL)
        return;
}

Gezegen *gezegenBul(const char *gezegenAdi, Gezegen *gezegenler, int gezegenSayisi)
{
    if (gezegenAdi == NULL || gezegenler == NULL || gezegenSayisi <= 0)
    {
        return NULL;
    }

    for (int i = 0; i < gezegenSayisi; i++)
    {
        if (strcasecmp(gezegenler[i].gezegenAdi, gezegenAdi) == 0)
        {
            return &gezegenler[i];
        }
    }
    return NULL;
}

void Gezegen_ZamaniIleriAl(Gezegen *g, int saat)
{
    g->birikmisSaat += saat;
    int eklenecekGun = g->birikmisSaat / g->gunlukSaatSayisi;
    g->birikmisSaat %= g->gunlukSaatSayisi;

    if (eklenecekGun > 0)
    {
        g->mevcutTarih.tm_mday += eklenecekGun;
        if (mktime(&(g->mevcutTarih)) == -1)
        {
            printf("Tarih güncellenemedi.\n");
        }
    }
}

const char *Gezegen_GetGezegenAdi(Gezegen *g)
{
    return g->gezegenAdi;
}

int Gezegen_GetGunlukSaatSayisi(Gezegen *g)
{
    return g->gunlukSaatSayisi;
}

struct tm Gezegen_GetMevcutTarih(Gezegen *g)
{
    return g->mevcutTarih;
}

void Gezegen_mevcutTarihiYaziOlarakGetir(Gezegen *g, char *output)
{
    strftime(output, MAX_DATE_STRING, "%d.%m.%Y", &(g->mevcutTarih));
}

int Gezegen_TarihAyniMi(Gezegen *g, const char *digerTarihStr)
{
    if (digerTarihStr == NULL || strlen(digerTarihStr) == 0)
    {

        return 0;
    }

    struct tm digerTarih;
    if (!parseTarih(digerTarihStr, &digerTarih))
    {

        return 0;
    }

    int ayniYil = g->mevcutTarih.tm_year == digerTarih.tm_year;
    int ayniAy = g->mevcutTarih.tm_mon == digerTarih.tm_mon;
    int ayniGun = g->mevcutTarih.tm_mday == digerTarih.tm_mday;

    return (ayniYil && ayniAy && ayniGun);
}

void Gezegen_SuGunSonrasiTarih(Gezegen *g, int kacGunSonra, char *output)
{
    struct tm yeniTarih = g->mevcutTarih;
    yeniTarih.tm_mday += kacGunSonra;
    mktime(&yeniTarih);
    strftime(output, MAX_DATE_STRING, "%d.%m.%Y", &yeniTarih);
}

void Gezegen_SuSaatSonrasiTarih(Gezegen *g, int kacSaatSonra, char *output)
{
    int kacGunSonra = kacSaatSonra / g->gunlukSaatSayisi;
    Gezegen_SuGunSonrasiTarih(g, kacGunSonra, output);
}

void Gezegen_ToString(Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir(g, tarihStr); // Tarih formatını al
    snprintf(output, 200, "--- %s --- Gunluk Saat: %d, Baslangic Tarihi: %s", g->gezegenAdi, g->gunlukSaatSayisi, tarihStr);
}
