

#include "SatirListesi.hpp"
#include "ConsolePosition.hpp"

SatirListesiDugum* SatirListesi::FindPreviousByPosition(int index)throw (NoSuchElement) {
    if (index < 0 || index > size) throw NoSuchElement("No Such Element");
    SatirListesiDugum *prv = head;
    int i = 1;
    for (SatirListesiDugum*itr = head; itr->sonraki != NULL && i != index; itr = itr->sonraki, i++) {
        prv = prv->sonraki;
    }
    return prv;
}

SatirListesi::SatirListesi() {
    head = NULL;
    size = 0;
}

int SatirListesi::Count()const {
    return size;
}

bool SatirListesi::isEmpty()const {
    return size == 0;
}

void SatirListesi::add(const int& item) {
    insert(size, item);
}

void SatirListesi::insert(int index, const int& item) {
    if (index < 0 || index > size) throw "Index out of Range";
    if (index == 0) {
        head = new SatirListesiDugum(item, head);
        if (head->sonraki != NULL) head->sonraki->onceki = head;
    } else {
        SatirListesiDugum *prv = FindPreviousByPosition(index);
        prv->sonraki = new SatirListesiDugum(item, prv->sonraki, prv);
        if (prv->sonraki->sonraki != NULL)
            prv->sonraki->sonraki->onceki = prv->sonraki;
    }
    size++;
}

const int& SatirListesi::first()throw (NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return head->veri;
}

const int& SatirListesi::last()throw (NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return FindPreviousByPosition(size)->veri;
}

int SatirListesi::indexOf(const int& item)throw (NoSuchElement) {
    int index = 0;
    for (SatirListesiDugum *itr = head; itr != NULL; itr = itr->sonraki) {
        if (itr->veri == item) return index;
        index++;
    }
    throw NoSuchElement("No Such Element");
}

void SatirListesi::remove(const int& item) {
    int index = indexOf(item);
    removeAt(index);
}

void SatirListesi::removeAt(int index) {
    if (index < 0 || index >= size) throw "Index out of Range";
    SatirListesiDugum *del;
    if (index == 0) {
        del = head;
        head = head->sonraki;
        if (head != NULL) head->onceki = NULL;
    } else {
        SatirListesiDugum *prv = FindPreviousByPosition(index);
        del = prv->sonraki;
        prv->sonraki = del->sonraki;
        if (del->sonraki != NULL)
            del->sonraki->onceki = prv;
    }
    size--;
    delete del;
}

bool SatirListesi::find(const int& item) {
    for (SatirListesiDugum *itr = head; itr != NULL; itr = itr->sonraki) {
        if (itr->veri == item) return true;
    }
    return false;
}

void SatirListesi::reverse() {
    for (SatirListesiDugum *itr = head; itr != NULL;) {
        SatirListesiDugum *tmp = itr->sonraki;
        itr->sonraki = itr->onceki;
        itr->onceki = tmp;
        if (tmp == NULL) {
            head = itr;
            break;
        }
        itr = tmp;
    }
}

const int& SatirListesi::elementAt(int index)throw (NoSuchElement) {
    if (index < 0 || index >= size) throw NoSuchElement("No Such Element");
    if (index == 0) return head->veri;
    return FindPreviousByPosition(index)->sonraki->veri;
}

void SatirListesi::clear() {
    while (!isEmpty())
        removeAt(0);
}

ostream& operator <<(ostream& screen, SatirListesi& rgt) {

    for (SatirListesiDugum *itr = rgt.head; itr != NULL; itr = itr->sonraki) {
        screen<<itr<<"\n";
        screen<<"----------\n";
        screen<<"|"<<setw(5)<<itr->veri<<setw(5)<<"|"<<endl;
        screen<<"----------\n";
        screen<<"|"<<itr->sonraki<<setw(3)<<"|\n";
        screen<<"----------\n\n";
    }
    screen << endl;
    return screen;
}

void SatirListesi::printDugumsFromPositionInReverseOrder(int index)throw (NoSuchElement) {
    if (index < 0 || index >= size) throw NoSuchElement("No Such Element");
    for (SatirListesiDugum *itr = FindPreviousByPosition(index + 1); itr != NULL; itr = itr->onceki) {
        
        cout << itr->veri << " <-> ";
    }
    cout << endl;
}

void SatirListesi::printReverseOrder() {
    printDugumsFromPositionInReverseOrder(size - 1);
}
void SatirListesi::yazdirSatirListesi(int x,int y){
    int yIndex=y; 
    ConsolePosition.gotoxy(x,yIndex);
    cout<<"^^^^^^^^^^\n"; 
     for (SatirListesiDugum *itr = this->head; itr != NULL; itr = itr->sonraki) {
      
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<itr<<"\n";
        
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<"----------\n";
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<"|"<<setw(5)<<itr->veri<<setw(5)<<"|"<<endl;
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<"----------\n";
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<"|"<<itr->sonraki<<setw(3)<<"|\n";
        ConsolePosition.gotoxy(x,++yIndex);
        cout<<"----------\n\n";
    }
}

SatirListesi::~SatirListesi() {
    clear();
}
