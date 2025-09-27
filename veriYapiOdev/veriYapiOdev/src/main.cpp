#include <cstdlib>
#include "SatirListesi.hpp"
#include "YoneticiListesi.hpp"
#include "DosyaOku.hpp" 
#include "ConsoldaGoruntule.hpp"
#include  "Exception.hpp"

using namespace std;

int main(int argc, char** argv) {

    DosyaOku * readingFile = new DosyaOku("veriler.txt");

    YoneticiListesi *yoneticiListesi = readingFile->GetFillYoneticiListesi();

    ConsoldaGoruntule *console = new ConsoldaGoruntule(yoneticiListesi);
    yoneticiListesi->sortByAverage();
    string karakter = "";
    do {
        console->yazdirYoneticiListesi();
        cin>>karakter;
        if (karakter == "c") {
            Yon yon = ust;
            console->setDurum(yon);
        } else if (karakter == "z") {
            Yon yon = alt;
            console->setDurum(yon);
        } else if (karakter == "k") {
            int rastgeleIndex = 0;
            try {
                rastgeleIndex = console->RastgeleSelectedDugumGoruntule();
            } catch (...) {
                continue;

            }
            cin>>karakter;
            if (karakter == "k") {

                console->RastgeleSelectedDugumSil(rastgeleIndex);
                yoneticiListesi->sortByAverage();

            }
        } else if (karakter == "p") {
            console->YoneticiDugumSil();
        } else if (karakter == "d") {
            console->SetSayfa(ustSayfa);
        } else if (karakter == "a") {
            console->SetSayfa(altSayfa);
        }


    } while (karakter != "q");



    return 0;



}