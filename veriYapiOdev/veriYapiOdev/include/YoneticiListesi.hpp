

#ifndef YONETICILISTESI_HPP
#define YONETICILISTESI_HPP

#include <iostream>

#include "SatirListesi.hpp"
#include "YoneticiDugum.hpp"
#include <stdlib.h>    
#include <time.h>       
#include "IndexOutOfBounds.hpp"
#include "ConsolePosition.hpp"

class YoneticiListesi {
private:
    YoneticiDugum *head;
    int size;

    YoneticiDugum* FindPreviousByPosition(int index)throw (NoSuchElement);

    YoneticiDugum* FindPosition(int index)throw (NoSuchElement);

public:

    YoneticiListesi();
    int Count()const;
    bool isEmpty()const;
    void add(SatirListesi*& item);
    void insert(int index, SatirListesi*& item);
    SatirListesi*& first()throw (NoSuchElement);
    SatirListesi*& last()throw (NoSuchElement);
    int indexOf(SatirListesi*& item)throw (NoSuchElement);
    void remove(SatirListesi*& item);
    void rastgeleRemoveAtSatirListesi(int index, int inlineIndex)throw (IndexOutOfBounds, NoSuchElement);
    void ortHesapla(int index);
    int  rastgeleGenerator(int index)throw (IndexOutOfBounds, NoSuchElement);
    void removeAt(int index);
    void moveDugum(int from, int to)throw (IndexOutOfBounds);
    bool find(SatirListesi*& item);
    void reverse();
    void sortByAverage();
    SatirListesi*& elementAt(int index)throw (NoSuchElement);
    void clear();
    void yazdirIndex(int index, int x, int y);
    ~YoneticiListesi();

};


#endif 

