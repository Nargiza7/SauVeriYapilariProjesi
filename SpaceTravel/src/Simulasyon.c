/** 
* 
* @author Nargiza Zhyrgalbek Kyzy nargiza.kyzy@ogr.sakarya.edu.tr 
* @since 15.05.2025
* <p> 
*  Main Class diğer sınıfları burada kullanıyoruz.
* </p> 
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Gezegen.h"
#include "Kisi.h"
#include "UzayAraci.h"
#include "DosyaOkuma.h"
#include "KayacGezegen.h"
#include "GazDeviGezegen.h"
#include "BuzDeviGezegen.h"
#include "CuceGezegen.h"

int gezegenNufusHesapla(const char *gezegenAdi, UzayAraci *araclar, int aracSayisi, Kisi *kisiler, int kisiSayisi);
UzayAraci *araciBul(const char *ad, UzayAraci *araclar, int aracSayisi);
void ekranTemizle();
void bilgileriGoster(int iterasyon, Gezegen *gezegenler, int gezegenSayisi, UzayAraci *araclar, int aracSayisi, Kisi *kisiler, int kisiSayisi);

void ekranTemizle()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void bilgileriGoster(int iterasyon, Gezegen *gezegenler, int gezegenSayisi, UzayAraci *araclar, int aracSayisi, Kisi *kisiler, int kisiSayisi)
{
    printf("\nToplam Gecen Saat: %d\n", iterasyon);

    int gezegenAlanGenisligi = 16;
    int tarihAlanGenisligi = 16;

    printf("\nGezegenler:\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        printf("%-*s", gezegenAlanGenisligi, gezegenler[i].gezegenAdi);
    }
    printf("\n");

    printf("Tarih:\t\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        char tarihStr[32];
        Gezegen_mevcutTarihiYaziOlarakGetir(&(gezegenler[i]), tarihStr);
        printf("%-*s", tarihAlanGenisligi, tarihStr);
    }
    printf("\n");

    printf("Nufus:\t\t");
    for (int i = 0; i < gezegenSayisi; i++)
    {
        int nufus = gezegenNufusHesapla(gezegenler[i].gezegenAdi, araclar, aracSayisi, kisiler, kisiSayisi);
        printf("%-*d", tarihAlanGenisligi, nufus);
    }
    printf("\n\n");

    printf("Uzay Araclari:\n");
    printf("Arac Adi \tDurum\t\tCikis\t\tVaris\t\tHedefe Kalan Saat\tHedefe Varacagi Tarih\n");
    for (int i = 0; i < aracSayisi; i++)
    {
        UzayAraci *arac = &araclar[i];
        const char *durumStr = getDurum(arac); // Aracın mevcut durumunu al
        const char *gosterilecekVarisTarihi;   // Son sütunda gösterilecek string
        char kalanSaatBuffer[20];              // Kalan saat için geçici buffer
        const char *kalanSaatStr;              // Kalan saat için gösterilecek string

        // Hedef Varis Tarihi Sütunu için Karar Verme
        if (strcmp(durumStr, "Vardi") == 0)
        {
            // Durum "Vardi" ise hesaplanan tarihi kullan
            gosterilecekVarisTarihi = getTahminiVarisTarihi(arac);
        }
        else if (strcmp(durumStr, "IMHA") == 0)
        {
            gosterilecekVarisTarihi = "--";
        }
        else
        {

            if (strcmp(arac->tahminiVarisTarihi, "Hesaplaniyor") == 0)
            {
                gosterilecekVarisTarihi = "Hesaplaniyor";
            }
            else
            {
                gosterilecekVarisTarihi = getTahminiVarisTarihi(arac);
            }
        }

        if (strcmp(durumStr, "Vardi") == 0)
        {
            kalanSaatStr = "0";
        }
        else if (strcmp(durumStr, "IMHA") == 0)
        {
            kalanSaatStr = "--";
        }
        else if (strcmp(durumStr, "Bekliyor") == 0)
        {

            kalanSaatStr = "--";
        }
        else
        {
            snprintf(kalanSaatBuffer, sizeof(kalanSaatBuffer), "%.0f", arac->kalanSaat);
            kalanSaatStr = kalanSaatBuffer;
        }

        // Satırı Yazdır
        printf("%-15s\t%-10s\t%-15s\t%-15s\t%-10s\t\t%-20s\n",
               arac->ad,
               durumStr,
               arac->kalkisGezegeni,
               arac->varisGezegeni,
               kalanSaatStr,
               gosterilecekVarisTarihi);
    }
}

int gezegenNufusHesapla(const char *gezegenAdi, UzayAraci *araclar, int aracSayisi, Kisi *kisiler, int kisiSayisi)
{

    int nufus = 0;
    for (int i = 0; i < kisiSayisi; i++)
    {

        if (!kisiler[i].hayattaMi)
            continue;

        UzayAraci *arac = araciBul(kisiler[i].uzayAraci, araclar, aracSayisi);
        if (arac != NULL && !arac->imhaEdildi)
        {

            if (strcmp(getMevcutKonum(arac), gezegenAdi) == 0)
            {
                nufus++;
            }
        }
    }

    return nufus;
}

UzayAraci *araciBul(const char *ad, UzayAraci *araclar, int aracSayisi)
{

    char tempAd[100];
    strncpy(tempAd, ad, sizeof(tempAd) - 1);
    tempAd[sizeof(tempAd) - 1] = '\0';

    for (int i = 0; i < aracSayisi; i++)
    {
        // Her iki adı da temizle
        char tempAracAd[100];
        strncpy(tempAracAd, araclar[i].ad, sizeof(tempAracAd) - 1);
        tempAracAd[sizeof(tempAracAd) - 1] = '\0';

        // Debug bilgisi
        if (tempAd)
            tempAd[strcspn(tempAd, "\r\n")] = '\0';
        if (tempAracAd)
            tempAracAd[strcspn(tempAracAd, "\r\n")] = '\0';

        if (strcasecmp(tempAracAd, tempAd) == 0)
        {

            return &araclar[i];
        }
    }

    return NULL;
}

int hepsiVardiMi(UzayAraci *araclar, int aracSayisi)
{
    for (int i = 0; i < aracSayisi; i++)
    {
        if (!varisGerceklestiMi(&(araclar[i])))
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int gezegenSayisi = 0, kisiSayisi = 0, aracSayisi = 0;

    Gezegen *gezegenler = gezegenleriOku("Gezegenler.txt", &gezegenSayisi);
    if (gezegenler == NULL)
    {

        return 1;
    }

    Kisi *kisiler = kisileriOku("Kisiler.txt", &kisiSayisi);
    if (kisiler == NULL)
    {

        return 1;
    }

    UzayAraci *araclar = uzayAraclariniOku("Araclar.txt", &aracSayisi);
    if (araclar == NULL)
    {

        return 1;
    }

    int iterasyon = 0;
    int hepsiVardi = 0;

    while (!hepsiVardi)
    {
        iterasyon++;

        ekranTemizle();

        for (int i = 0; i < gezegenSayisi; i++)
        {
            Gezegen_ZamaniIleriAl(&(gezegenler[i]), 1);
        }

        for (int i = 0; i < kisiSayisi; i++)
        {

            zamanGecir(&(kisiler[i]), 1, araclar, aracSayisi, gezegenler, gezegenSayisi);
        }

        for (int i = 0; i < aracSayisi; i++)
        {
            UzayAraci *arac = &araclar[i];

            ekipDurumunuKontrolEt(arac, kisiler, kisiSayisi);

            Gezegen *cikis = NULL, *varis = NULL;
            for (int j = 0; j < gezegenSayisi; j++)
            {
                if (strcmp(gezegenler[j].gezegenAdi, arac->kalkisGezegeni) == 0)
                    cikis = &gezegenler[j];
                if (strcmp(gezegenler[j].gezegenAdi, arac->varisGezegeni) == 0)
                    varis = &gezegenler[j];
            }

            if (cikis && varis)
            {
                if (strcmp(arac->durum, "Bekliyor") == 0 && strcmp(arac->kalkisGezegeni, cikis->gezegenAdi) == 0)
                {
                    char gezegenTarihStr[20];
                    Gezegen_mevcutTarihiYaziOlarakGetir(cikis, gezegenTarihStr);
                }

                durumuGuncelle(arac, cikis, varis);

                if (strcmp(arac->durum, "Yolda") == 0)
                {
                    // printf("Arac yolculuga basladi.\n");
                }

                yolculukEt(arac, 1);
            }
            else
            {
                printf("Cikis veya varis gezegeni eksik.\n");
            }
        }

        bilgileriGoster(iterasyon, gezegenler, gezegenSayisi, araclar, aracSayisi, kisiler, kisiSayisi);

        hepsiVardi = hepsiVardiMi(araclar, aracSayisi);
    }

    printf("\n---------------------------------------------------------\n");
    printf("Tum uzay araclari hedeflerine ulasti. Simulasyon sona erdi.\n");

    free(gezegenler);
    free(kisiler);
    free(araclar);

    return 0;
}
