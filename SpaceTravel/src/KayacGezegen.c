/** 
* 
* @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
* @since 15.05.2025
* <p> 
* 	Kayac Gezegen
* </p> 
*/
#include "KayacGezegen.h"

KayacGezegen *KayacGezegen_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi)
{
    KayacGezegen *this = (KayacGezegen *)malloc(sizeof(KayacGezegen));
    if (this == NULL)
        return NULL;

    Gezegen_Init(&this->super, gezegenAdi, GEZEGEN_TURU_KAYAC, gunlukSaatSayisi, baslangicTarihi);

    this->super.getYaslanmaFaktoru = &KayacGezegen_GetYaslanmaFaktoru;
    this->super.toString = &KayacGezegen_ToString;
    this->super.yoket = &KayacGezegen_Yoket;

    return this;
}

double KayacGezegen_GetYaslanmaFaktoru(const Gezegen *g)
{
    return 1.0;
}

void KayacGezegen_ToString(const Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir((Gezegen *)g, tarihStr);
    snprintf(output, 200, "--- Kayac Gezegen: %s --- Gunluk Saat: %d, Mevcut Tarih: %s, Yaslanma Faktoru: %.2lf",
             g->gezegenAdi, g->gunlukSaatSayisi, tarihStr, g->getYaslanmaFaktoru(g));
}

void KayacGezegen_Yoket(Gezegen *g)
{
    if (g == NULL)
        return;
    free(g);
}