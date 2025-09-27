#ifndef KAYACGEZEGEN_H // Header guard güncellendi
#define KAYACGEZEGEN_H

#include "Gezegen.h" // Temel Gezegen sınıfı dahil edildi

// Yapı adı KayaGezegen yerine KayacGezegen olarak değiştirildi
struct KayacGezegen {
    Gezegen super; // Kalıtım benzetimi (base class member)
    // Kayac gezegenine özgü ek özellikler buraya eklenebilir
    // Örneğin: char kayaTuru[MAX_NAME_LENGTH];
};
typedef struct KayacGezegen KayacGezegen; // typedef güncellendi

// Fonksiyon prototipleri KayacGezegen adıyla güncellendi
KayacGezegen* KayacGezegen_Olustur(const char *gezegenAdi, int gunlukSaatSayisi, const char *baslangicTarihi);
double KayacGezegen_GetYaslanmaFaktoru(const Gezegen* g); // Override
void KayacGezegen_ToString(const Gezegen* g, char* output); // Override
void KayacGezegen_Yoket(Gezegen* g); // Override

#endif // KAYACGEZEGEN_H // Header guard güncellendi