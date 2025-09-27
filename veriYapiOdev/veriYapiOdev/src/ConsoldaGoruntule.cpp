
#include "ConsoldaGoruntule.hpp"

ConsoldaGoruntule::ConsoldaGoruntule(YoneticiListesi* yonetici) {
    this->yonetici = yonetici;
    if (this->yonetici->Count() < BirSayfadaGoster) {
        this->sonOffset = this->yonetici->Count();
    } else {
        this->sonOffset = BirSayfadaGoster;
    }

    this->baslaOffset = BaslaOffset;

}

    void ConsoldaGoruntule::setOffsets() {
    int sayfa = durum / BirSayfadaGoster;
    this->baslaOffset = BirSayfadaGoster*sayfa;
    this->sonOffset = BirSayfadaGoster * (sayfa + 1);
    if (this->sonOffset >= this->yonetici->Count()) {
        this->sonOffset = this->yonetici->Count();

    }
}

void ConsoldaGoruntule::setDurum(Yon dr) {

    if (dr == ust) {
        if (durum >= this->yonetici->Count() - 1) {
            return;
        }
        ++durum;
        setOffsets();
    } else if (dr == alt) {
        if (durum <= 0) {

            return;
        }
        --durum;
        setOffsets();
    } else if (dr == yenile) {
        setOffsets();
    }

}

void ConsoldaGoruntule::SetSayfa(SayfaYonu sy) {
    if (sy == altSayfa) {
        for (int i = 0; i < BirSayfadaGoster; ++i) {
            this->setDurum(alt);
        }
    } else if (sy == ustSayfa) {
        for (int i = 0; i < BirSayfadaGoster; ++i) {
            this->setDurum(ust);
        }
    }
}

void ConsoldaGoruntule::yazdirYoneticiListesi() {

    int count = yonetici->Count();
    system("cls");
    if (count == 0) {
        cout << "Görüntülenecek bir Yönetici listesi yok\n";
        exit(1);
        return;
    }


    ConsolePosition.gotoxy(0, 0);
    if (this->baslaOffset == 0) {
        cout << "<--ilk--";
    } else {
        cout << "<---geri--";
    }


    int showingDugumCount = this->sonOffset - this->baslaOffset;
    showingDugumCount *= 13;


    ConsolePosition.gotoxy(showingDugumCount, 0);


    if (this->sonOffset == yonetici->Count()) {
        cout << "--son-->";
    } else {
        cout << "--ileri-->";
    }
    for (int i = this->baslaOffset; i<this->sonOffset; ++i) {


        int mod = i % BirSayfadaGoster;
        this->yonetici->yazdirIndex(i, 15 * mod, 1);

    }
    this->yazdirSelectedSatirListesi((this->durum % BirSayfadaGoster) *15, 9);
}

 void ConsoldaGoruntule::yazdirSelectedSatirListesi(int x, int y) {
        this->yonetici->elementAt(this->durum)->yazdirSatirListesi(x, y);

    }
  int ConsoldaGoruntule::RastgeleSelectedDugumGoruntule()throw (IndexOutOfBounds, NoSuchElement) {

        int rastgeleSelected = this->yonetici->rastgeleGenerator(this->durum);
        int xPosition = ((this->durum % BirSayfadaGoster) + 1)*15;
        int yPosition = (rastgeleSelected)*6;
        yPosition += 12;
        ConsolePosition.gotoxy(xPosition, yPosition);
        cout << "<--silinecek";
        yPosition = this->yonetici->elementAt(this->durum)->Count()*6 + 12;

        ConsolePosition.gotoxy(0, yPosition - 1);


        return rastgeleSelected;

    }
  void ConsoldaGoruntule::YoneticiDugumSil() {
        this->yonetici->removeAt(this->durum);
       this->setDurum(yenile);
      
        if(this->durum==this->sonOffset){
            this->durum--;
        }
         this->setDurum(yenile);

   

    }
  void ConsoldaGoruntule::RastgeleSelectedDugumSil(int rastgeleIndex)throw (IndexOutOfBounds, NoSuchElement) {
        this->yonetici->rastgeleRemoveAtSatirListesi(this->durum, rastgeleIndex);
    }
