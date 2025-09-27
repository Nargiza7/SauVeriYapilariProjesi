/**
 *
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 * @since 15.05.2025
 * <p>
 * 	Kisi Nesnesi
 * </p>
 */
#include "Kisi.h"
#include "UzayAraci.h"
#include "Gezegen.h"
#include <string.h>
#include <stdio.h>
#include <math.h>

void Kisi_Init(Kisi *k, const char *isim, int yas, int kalanOmur, const char *uzayAraci)
{
    strncpy(k->isim, isim, sizeof(k->isim) - 1);
    k->isim[sizeof(k->isim) - 1] = '\0';

    k->yas = yas;
    k->kalanOmur = kalanOmur > 0 ? kalanOmur : 1;

    strncpy(k->uzayAraci, uzayAraci, sizeof(k->uzayAraci) - 1);
    k->uzayAraci[sizeof(k->uzayAraci) - 1] = '\0';

    k->hayattaMi = 1;
}

void zamanGecir(Kisi *kisi, int saat, UzayAraci *araclar, int aracSayisi, Gezegen *gezegenler, int gezegenSayisi)
{
    if (saat <= 0 || !kisi->hayattaMi)
        return;

    double yaslanmaFaktoru = 1.0;

    UzayAraci *arac = araciBul(kisi->uzayAraci, araclar, aracSayisi);

    if (arac != NULL && !imhaDurumu(arac))
    {
        const char *mevcutKonum = getMevcutKonum(arac);

        if (strcmp(mevcutKonum, "Yolda") != 0)
        {

            Gezegen *gezegen = gezegenBul(mevcutKonum, gezegenler, gezegenSayisi);

            if (gezegen != NULL)
            {

                yaslanmaFaktoru = Gezegen_DefaultGetYaslanmaFaktoru((const Gezegen *)gezegen);
            }
        }
    }

    int yaslanmaMiktari = (int)(saat * yaslanmaFaktoru);

    kisi->kalanOmur -= yaslanmaMiktari;

    if (kisi->kalanOmur <= 0)
    {
        kisi->hayattaMi = false;
        kisi->kalanOmur = 0;
    }
}

const char *getIsim(Kisi *kisi)
{
    return kisi->isim;
}

int getYas(Kisi *kisi)
{
    return kisi->yas;
}

int getKalanOmur(Kisi *kisi)
{
    return kisi->kalanOmur;
}

const char *getUzayAraciAdi(Kisi *kisi)
{
    return kisi->uzayAraci;
}

int isHayattaMi(Kisi *kisi)
{
    return kisi->hayattaMi;
}
