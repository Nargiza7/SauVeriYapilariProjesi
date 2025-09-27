/** 
* 
* @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr 
* @since 15.05.2025
* <p> 
* 	Bir uzay aracının X gezegeninden Y gezegenine yaptığı yolculuk sırasında, 
*   bu sınıfta uzay aracının Y gezegenine varış tarihi hesaplanmaktadır..
* </p> 
*/
#include "ZamanHesaplama.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_DATE_STRING 20

int parseTarih(const char *tarihStr, struct tm *outDate)
{
    memset(outDate, 0, sizeof(struct tm));
    if (sscanf(tarihStr, "%d.%d.%d", &outDate->tm_mday, &outDate->tm_mon, &outDate->tm_year) == 3)
    {
        outDate->tm_year -= 1900; // Yıl bilgisi 1900'dan başlar
        outDate->tm_mon -= 1;     // Ay bilgisi 0-11 arasıdır
        return 1;
    }
    return 0;
}

// İki tarih arasındaki farkı saat cinsinden hesaplar
int tarihFarkiSaatOlarak(const char *baslangicTarihi, const char *bitisTarihi, int gunlukSaatSayisi)
{
    struct tm t1, t2;

    if (!parseTarih(baslangicTarihi, &t1) || !parseTarih(bitisTarihi, &t2))
    {
        printf("Geçersiz tarih formatı!\n");
        return -1;
    }

    time_t time1 = mktime(&t1);
    time_t time2 = mktime(&t2);

    if (time1 == (time_t)(-1) || time2 == (time_t)(-1))
    {
        printf("Tarih hesaplama hatasi!\n");
        return -1;
    }

    double farkGun = difftime(time2, time1) / (60 * 60 * 24);
    if (farkGun < 0)
    {
        printf("Tarih yönü hatali: bitis, baslangictan once.\n");
        return -1;
    }
    return (int)(farkGun * gunlukSaatSayisi);
}

// Mesafeye göre varış tarihini hesaplar
char *varisTarihiniHesapla(const char *kalkisTarihi, int kalkisGunlukSaat, double mesafeSaatCinsinden, int varisGunlukSaat, const char *varisMevcutTarih)
{
    struct tm varisTarih;
    if (!parseTarih(varisMevcutTarih, &varisTarih))
    {
        printf("Gecersiz varis tarihi formati!\n");
        return NULL;
    }

    int toplamSaat = (int)floor(mesafeSaatCinsinden);
    int eklenecekGun = toplamSaat / varisGunlukSaat;

    varisTarih.tm_mday += eklenecekGun;
    mktime(&varisTarih); 

    char *sonuc = malloc(MAX_DATE_STRING);
    strftime(sonuc, MAX_DATE_STRING, "%d.%m.%Y", &varisTarih);

    return sonuc;
}

char *tamYolculukTarihiniHesapla(const char *kalkisMevcutTarih, const char *uzayAraciKalkisTarihi, int kalkisGunlukSaat, double mesafeSaatCinsinden, const char *varisMevcutTarih, int varisGunlukSaat)
{
    // Bekleme süresi saat cinsinden hesaplanıyor
    int beklemeSuresiSaat = tarihFarkiSaatOlarak(kalkisMevcutTarih, uzayAraciKalkisTarihi, kalkisGunlukSaat);
    if (beklemeSuresiSaat < 0)
    {
        printf("Bekleme suresi hesaplanamadi!\n");
        return NULL;
    }

    // Toplam saat = bekleme + yolculuk
    int toplamSaat = beklemeSuresiSaat + (int)floor(mesafeSaatCinsinden);

    int toplamGun = toplamSaat / varisGunlukSaat;

    int yolculukGunSayisi = ((int)floor(mesafeSaatCinsinden)) / varisGunlukSaat;

    struct tm varisTarih;
    if (!parseTarih(varisMevcutTarih, &varisTarih))
    {
        printf("Gecersiz varis tarihi formati!\n");
        return NULL;
    }

    varisTarih.tm_mday += toplamGun;
    mktime(&varisTarih);

    char *sonuc = malloc(MAX_DATE_STRING);
    strftime(sonuc, MAX_DATE_STRING, "%d.%m.%Y", &varisTarih);
    return sonuc;
}
