/** 
* 
* @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr 
* @since 15.05.2025
* <p> 
*  Dosya Okuma Sınıfı
* </p> 
*/
#include "DosyaOkuma.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SATIR_BOYUTU 512

Gezegen *gezegenleriOku(const char *dosyaYolu, int *gezegenSayisi)
{
    FILE *dosya = fopen(dosyaYolu, "r");
    if (!dosya)
    {
        perror("Gezegen dosyasi acilamadi");
        *gezegenSayisi = 0;
        return NULL;
    }

    Gezegen *gezegenler = NULL;
    *gezegenSayisi = 0;
    char satir[SATIR_BOYUTU];

    while (fgets(satir, sizeof(satir), dosya))
    {
        satir[strcspn(satir, "\r\n")] = '\0';

        char *isim = strtok(satir, "#");
        char *turuStr = strtok(NULL, "#");
        char *gunlukSaatStr = strtok(NULL, "#");
        char *tarih = strtok(NULL, "#\r\n");

        if (isim && turuStr && gunlukSaatStr && tarih)
        {
            gezegenler = realloc(gezegenler, sizeof(Gezegen) * (*gezegenSayisi + 1));
            Gezegen *g = &gezegenler[*gezegenSayisi];

            int gezegenTuru = atoi(turuStr);
            int gunlukSaat = atoi(gunlukSaatStr);
            Gezegen_Init(g, isim, gezegenTuru, gunlukSaat, tarih);

            (*gezegenSayisi)++;
        }
        else
        {
            printf("Eksik veya hatali gezegen verisi: %s\n", satir);
        }
    }

    fclose(dosya);
    printf("Toplam okunan gezegen sayisi: %d\n", *gezegenSayisi);
    return gezegenler;
}

void temizle(char *str)
{
    if (!str)
        return;

    // Satır sonu karakterini temizle
    str[strcspn(str, "\n")] = 0;

    // Baştaki boşlukları geç
    while (*str == ' ' || *str == '\t')
        str++;

    // Sondaki boşlukları temizle
    char *son = str + strlen(str) - 1;
    while (son > str && (*son == ' ' || *son == '\t'))
    {
        *son = '\0';
        son--;
    }
}

UzayAraci *uzayAraclariniOku(const char *dosyaYolu, int *aracSayisi)
{
    FILE *dosya = fopen(dosyaYolu, "r");
    if (!dosya)
    {
        perror("Uzay araci dosyasi acilamadi");
        *aracSayisi = 0;
        return NULL;
    }

    UzayAraci *araclar = NULL;
    *aracSayisi = 0;
    char satir[SATIR_BOYUTU];

    while (fgets(satir, sizeof(satir), dosya))
    {
        char *isim, *cikisGezegeni, *varisGezegeni, *cikisTarihi, *mesafeSaatStr;
        isim = strtok(satir, "#");
        cikisGezegeni = strtok(NULL, "#");
        varisGezegeni = strtok(NULL, "#");
        cikisTarihi = strtok(NULL, "#");
        mesafeSaatStr = strtok(NULL, "#\r\n");

        if (isim && cikisGezegeni && varisGezegeni && cikisTarihi && mesafeSaatStr)
        {
            araclar = realloc(araclar, sizeof(UzayAraci) * (*aracSayisi + 1));
            UzayAraci *a = &araclar[*aracSayisi];

            double mesafeSaat = atof(mesafeSaatStr);
            *a = UzayAraciOlustur(isim, cikisGezegeni, varisGezegeni, cikisTarihi, mesafeSaat);

            (*aracSayisi)++;
        }
        else
        {
            printf("Eksik veya hatali uzay araci verisi: %s\n", satir);
        }
    }

    fclose(dosya);
    printf("Toplam okunan uzay araci: %d\n", *aracSayisi);
    return araclar;
}

Kisi *kisileriOku(const char *dosyaYolu, int *kisiSayisi)
{
    FILE *dosya = fopen(dosyaYolu, "r");
    if (!dosya)
    {
        perror("Kisiler dosyasi acilamadi");
        *kisiSayisi = 0;
        return NULL;
    }

    Kisi *kisiler = NULL;
    *kisiSayisi = 0;
    char satir[SATIR_BOYUTU];

    while (fgets(satir, sizeof(satir), dosya))
    {
        char *isim, *yasStr, *kalanOmurStr, *uzayAraciIsmi;
        isim = strtok(satir, "#");
        yasStr = strtok(NULL, "#");
        kalanOmurStr = strtok(NULL, "#");

        uzayAraciIsmi = strtok(NULL, "#\r\n");

        if (isim && yasStr && kalanOmurStr && uzayAraciIsmi)
        {
            kisiler = realloc(kisiler, sizeof(Kisi) * (*kisiSayisi + 1));
            Kisi *k = &kisiler[*kisiSayisi];

            int yas = atoi(yasStr);
            int kalanOmur = atoi(kalanOmurStr);
            Kisi_Init(k, isim, yas, kalanOmur, uzayAraciIsmi);

            (*kisiSayisi)++;
        }
        else
        {
            printf("Eksik veya hatali kisi verisi: %s\n", satir);
        }
    }

    fclose(dosya);
    printf("Toplam okunan kisi sayisi: %d\n", *kisiSayisi);
    return kisiler;
}
