/** 
* 
* @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr 
* @since 15.05.2025
* <p> 
*  Buz Devi Gezegen
* </p> 
*/ 
#include "BuzDeviGezegen.h"

BuzDevi *BuzDevi_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi)
{
    BuzDevi *this = (BuzDevi *)malloc(sizeof(BuzDevi));
    if (this == NULL)
        return NULL;
    Gezegen_Init(&this->super, gezegenAdi, GEZEGEN_TURU_BUZ_DEVI, gunlukSaatSayisi, baslangicTarihi);
    this->super.getYaslanmaFaktoru = &BuzDevi_GetYaslanmaFaktoru;
    this->super.toString = &BuzDevi_ToString;
    this->super.yoket = &BuzDevi_Yoket;
    return this;
}
double BuzDevi_GetYaslanmaFaktoru(const Gezegen *g) { return 0.5; }
void BuzDevi_ToString(const Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir((Gezegen *)g, tarihStr);
    snprintf(output, 200, "--- Buz Devi: %s --- Gunluk Saat: %d, Mevcut Tarih: %s, Yaslanma Faktoru: %.2lf",
             g->gezegenAdi, g->gunlukSaatSayisi, tarihStr, g->getYaslanmaFaktoru(g));
}
void BuzDevi_Yoket(Gezegen *g) { free(g); }