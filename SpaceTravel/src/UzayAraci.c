/**
 *
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 * @since 15.05.2025
 * <p>
 * 	Uzay Araci
 * </p>
 */
#include "UzayAraci.h"
#include "ZamanHesaplama.h"
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "Kisi.h"

UzayAraci UzayAraciOlustur(const char *ad, const char *kalkisGezegeni, const char *varisGezegeni,
                           const char *kalkisTarihi, double mesafeSaatCinsinden)
{
    UzayAraci uzayAraci;
    memset(&uzayAraci, 0, sizeof(UzayAraci));

    strncpy(uzayAraci.ad, ad, sizeof(uzayAraci.ad) - 1);
    strncpy(uzayAraci.kalkisGezegeni, kalkisGezegeni, sizeof(uzayAraci.kalkisGezegeni) - 1);
    strncpy(uzayAraci.varisGezegeni, varisGezegeni, sizeof(uzayAraci.varisGezegeni) - 1);
    strncpy(uzayAraci.kalkisTarihi, kalkisTarihi, sizeof(uzayAraci.kalkisTarihi) - 1);
    uzayAraci.mesafeSaatCinsinden = mesafeSaatCinsinden;
    uzayAraci.kalanSaat = mesafeSaatCinsinden;
    strncpy(uzayAraci.durum, "Bekliyor", sizeof(uzayAraci.durum) - 1);
    strncpy(uzayAraci.tahminiVarisTarihi, "Hesaplaniyor", sizeof(uzayAraci.tahminiVarisTarihi) - 1);
    uzayAraci.imhaEdildi = false;

    return uzayAraci;
}
void durumuGuncelle(UzayAraci *uzayAraci, Gezegen *kalkisGezegen, Gezegen *varisGezegen)
{
    if (uzayAraci == NULL || kalkisGezegen == NULL || varisGezegen == NULL)
    {
        return;
    }

    if (uzayAraci->imhaEdildi)
    {
        strncpy(uzayAraci->durum, "IMHA", sizeof(uzayAraci->durum) - 1);
        uzayAraci->durum[sizeof(uzayAraci->durum) - 1] = '\0';
        return;
    }

    if (strcmp(uzayAraci->tahminiVarisTarihi, "Hesaplaniyor") == 0)
    {
        ilkTahminiVarisTarihiniHesapla(uzayAraci, kalkisGezegen, varisGezegen);
    }

    if (strcmp(uzayAraci->durum, "Bekliyor") == 0 &&
        strcmp(uzayAraci->kalkisGezegeni, kalkisGezegen->gezegenAdi) == 0 &&
        Gezegen_TarihAyniMi(kalkisGezegen, uzayAraci->kalkisTarihi))
    {
        strncpy(uzayAraci->durum, "Yolda", sizeof(uzayAraci->durum) - 1);
        uzayAraci->durum[sizeof(uzayAraci->durum) - 1] = '\0';
    }
}

void yolculukEt(UzayAraci *uzayAraci, int saat)
{
    if (uzayAraci->imhaEdildi)
        return;

    if (strcmp(uzayAraci->durum, "Yolda") == 0)
    {
        uzayAraci->kalanSaat -= saat;
        if (uzayAraci->kalanSaat <= 0)
        {
            uzayAraci->kalanSaat = 0;
            strncpy(uzayAraci->durum, "Vardi", sizeof(uzayAraci->durum) - 1);
        }
    }
}

void ekipDurumunuKontrolEt(UzayAraci *uzayAraci, Kisi *kisiler, size_t kisiSayisi)
{
    bool biriHayatta = false;
    for (size_t i = 0; i < kisiSayisi; i++)
    {
        if (strcmp(kisiler[i].uzayAraci, uzayAraci->ad) == 0 && kisiler[i].hayattaMi)
        {
            biriHayatta = true;
            break;
        }
    }

    if (!biriHayatta)
    {
        uzayAraci->imhaEdildi = true;
        strncpy(uzayAraci->durum, "IMHA", sizeof(uzayAraci->durum) - 1);
        uzayAraci->durum[sizeof(uzayAraci->durum) - 1] = '\0';
    }
}

void ilkTahminiVarisTarihiniHesapla(UzayAraci *uzayAraci, Gezegen *kalkisGezegen, Gezegen *varisGezegen)
{
    char kalkisTarihiStr[20];
    strftime(kalkisTarihiStr, sizeof(kalkisTarihiStr), "%d.%m.%Y", &kalkisGezegen->mevcutTarih);

    // Varış gezegeninin mevcut tarihini de string'e çevir
    char varisTarihiStr[20];
    strftime(varisTarihiStr, sizeof(varisTarihiStr), "%d.%m.%Y", &varisGezegen->mevcutTarih);

    char *varisTarihi = tamYolculukTarihiniHesapla(
        kalkisTarihiStr, uzayAraci->kalkisTarihi,
        kalkisGezegen->gunlukSaatSayisi,
        uzayAraci->mesafeSaatCinsinden,
        varisTarihiStr,
        varisGezegen->gunlukSaatSayisi);

    if (varisTarihi != NULL)
    {
        // snprintf kullanarak daha güvenli kopyalama:
        snprintf(uzayAraci->tahminiVarisTarihi, sizeof(uzayAraci->tahminiVarisTarihi), "%s", varisTarihi);
        free(varisTarihi);
    }
}

const char *getMevcutKonum(UzayAraci *arac)
{
    if (strcmp(arac->durum, "Bekliyor") == 0)
    {
        return arac->kalkisGezegeni;
    }
    else if (strcmp(arac->durum, "Vardi") == 0)
    {
        return arac->varisGezegeni;
    }
    else
    {
        return "Yolda";
    }
}

const char *getDurum(UzayAraci *uzayAraci)
{
    return uzayAraci->durum;
}

bool varisGerceklestiMi(UzayAraci *uzayAraci)
{
    return strcmp(uzayAraci->durum, "Vardi") == 0 || uzayAraci->imhaEdildi;
}

const char *getTahminiVarisTarihi(UzayAraci *uzayAraci)
{
    if (uzayAraci->imhaEdildi)
        return "IMHA";
    else
        return uzayAraci->tahminiVarisTarihi;
}

bool imhaDurumu(UzayAraci *uzayAraci)
{
    return uzayAraci->imhaEdildi;
}
