/**
 *
 * @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr
 * @since 15.05.2025
 * <p>
 *  Gaz Devi Gezegen
 * </p>
 */
#include "GazDeviGezegen.h"

GazDevi *GazDevi_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi)
{
    GazDevi *this = (GazDevi *)malloc(sizeof(GazDevi));
    if (this == NULL)
        return NULL;
    Gezegen_Init(&this->super, gezegenAdi, GEZEGEN_TURU_GAZ_DEVI, gunlukSaatSayisi, baslangicTarihi);
    this->super.getYaslanmaFaktoru = &GazDevi_GetYaslanmaFaktoru;
    this->super.toString = &GazDevi_ToString;
    this->super.yoket = &GazDevi_Yoket;
    return this;
}
double GazDevi_GetYaslanmaFaktoru(const Gezegen *g) { return 0.1; }
void GazDevi_ToString(const Gezegen *g, char *output)
{
    char tarihStr[MAX_DATE_STRING];
    Gezegen_mevcutTarihiYaziOlarakGetir((Gezegen *)g, tarihStr);
    snprintf(output, 200, "--- Gaz Devi: %s --- Gunluk Saat: %d, Mevcut Tarih: %s, Yaslanma Faktoru: %.2lf",
             g->gezegenAdi, g->gunlukSaatSayisi, tarihStr, g->getYaslanmaFaktoru(g));
}
void GazDevi_Yoket(Gezegen *g) { free(g); }