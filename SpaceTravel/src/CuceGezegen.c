/**
 *
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 * @since 15.05.2025
 * <p>
 *  Cuce Gezegen
 * </p>
 */
#include "CuceGezegen.h"

CuceGezegen *CuceGezegen_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi)
{
    CuceGezegen *this = (CuceGezegen *)malloc(sizeof(CuceGezegen));
    if (this == NULL)
        return NULL;
    Gezegen_Init(&this->super, gezegenAdi, GEZEGEN_TURU_CUCE, gunlukSaatSayisi, baslangicTarihi);
    this->super.getYaslanmaFaktoru = &CuceGezegen_GetYaslanmaFaktoru;
    this->super.toString = &CuceGezegen_ToString;
    this->super.yoket = &CuceGezegen_Yoket;
    return this;
}
double CuceGezegen_GetYaslanmaFaktoru(const Gezegen *g) { return 0.01; }
void CuceGezegen_ToString(const Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir((Gezegen *)g, tarihStr);
    snprintf(output, 200, "--- Cüce Gezegen: %s --- Gunluk Saat: %d, Mevcut Tarih: %s, Yaslanma Faktoru: %.2lf",
             g->gezegenAdi, g->gunlukSaatSayisi, tarihStr, g->getYaslanmaFaktoru(g));
}
void CuceGezegen_Yoket(Gezegen *g) { free(g); }