
#ifndef SATIRLISTESI_HPP
#define SATIRLISTESI_HPP

#include "SatirListesiDugum.hpp"
#include "NoSuchElement.hpp"
#include <iomanip>

class SatirListesi {
private:
    SatirListesiDugum *head;
    int size;

    SatirListesiDugum* FindPreviousByPosition(int index)throw (NoSuchElement);
public:
    SatirListesi();
    int Count()const;
    bool isEmpty()const;
    void add(const int& item);
    void insert(int index, const int& item);
    const int& first()throw (NoSuchElement);
    const int& last()throw (NoSuchElement);
    int indexOf(const int& item)throw (NoSuchElement);
    void remove(const int& item);
    void removeAt(int index);
    bool find(const int& item);
    void reverse();
    const int& elementAt(int index)throw (NoSuchElement);
    void clear();
    friend ostream& operator<<(ostream& screen, SatirListesi& rgt);
    void printDugumsFromPositionInReverseOrder(int index)throw (NoSuchElement);
    void printReverseOrder();
    void yazdirSatirListesi(int x, int y);
    ~SatirListesi();

};


#endif 

