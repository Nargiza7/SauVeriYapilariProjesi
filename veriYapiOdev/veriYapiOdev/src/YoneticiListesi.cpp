
#include "YoneticiListesi.hpp"

YoneticiDugum* YoneticiListesi::FindPreviousByPosition(int index)throw (NoSuchElement) {
    if (index < 0 || index > size) throw NoSuchElement("No Such Element");
    YoneticiDugum *prv = head;
    int i = 1;
    for (YoneticiDugum *itr = head; itr->sonraki != NULL && i != index; itr = itr->sonraki, i++) {
        prv = prv->sonraki;
    }
    return prv;
}

YoneticiDugum* YoneticiListesi::FindPosition(int index)throw (NoSuchElement) {
    if (index < 0 || index >= size) throw NoSuchElement("No Such Element");
    return this->FindPreviousByPosition(index + 1);

}

YoneticiListesi::YoneticiListesi() {
    head = NULL;
    size = 0;
}

int YoneticiListesi::Count()const {
    return size;
}

bool YoneticiListesi::isEmpty()const {
    return size == 0;
}

void YoneticiListesi::add(SatirListesi*& item) {
    insert(size, item);
}

void YoneticiListesi::insert(int index, SatirListesi*& item) {
    if (index < 0 || index > size) throw "Index out of Range";
    if (index == 0) {
        head = new YoneticiDugum(item, head);
        if (head->sonraki != NULL) head->sonraki->onceki = head;
    } else {
        YoneticiDugum *prv = FindPreviousByPosition(index);
        prv->sonraki = new YoneticiDugum(item, prv->sonraki, prv);
        if (prv->sonraki->sonraki != NULL)
            prv->sonraki->sonraki->onceki = prv->sonraki;
    }
    size++;
}

SatirListesi*& YoneticiListesi::first()throw (NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return head->veri;
}

SatirListesi*& YoneticiListesi::last()throw (NoSuchElement) {
    if (isEmpty()) throw NoSuchElement("No Such Element");
    return FindPreviousByPosition(size)->veri;
}

int YoneticiListesi::indexOf(SatirListesi*& item)throw (NoSuchElement) {
    int index = 0;
    for (YoneticiDugum *itr = head; itr != NULL; itr = itr->sonraki) {
        if (itr->veri == item) return index;
        index++;
    }
    throw NoSuchElement("No Such Element");
}

void YoneticiListesi::remove(SatirListesi*& item) {
    int index = indexOf(item);
    removeAt(index);
}

void YoneticiListesi::rastgeleRemoveAtSatirListesi(int index, int inlineIndex)throw (IndexOutOfBounds, NoSuchElement) {

    int count = this->Count();
    if (index < 0 || index >= count)
        throw IndexOutOfBounds("Index out of bounds");

    SatirListesi* satirListesi = this->elementAt(index);

    satirListesi->removeAt(inlineIndex);
    ortHesapla(index);

}

void YoneticiListesi::ortHesapla(int index) {
    YoneticiDugum* yoneticiDugum = this->FindPosition(index);

    if (yoneticiDugum == NULL) {

        throw "hata";
    }


    double total = 0;
    if (yoneticiDugum->veri->isEmpty()) {

        yoneticiDugum->ort = total;
        return;
    }


    int count = yoneticiDugum->veri->Count();
    for (int i = 0; i < count; ++i) {
        total += yoneticiDugum->veri->elementAt(i);
    }
    yoneticiDugum->ort = total / count;



}

int YoneticiListesi::rastgeleGenerator(int index)throw (IndexOutOfBounds, NoSuchElement) {
    int count = this->Count();

    if (index < 0 || index >= count)
        throw IndexOutOfBounds("Index out of bounds");

    srand(time(NULL));
    SatirListesi* satirListesi = this->elementAt(index);

    int range = satirListesi->Count();
    if (range == 0) {
        throw NoSuchElement("No Such Element");
    }
    int inlineIndex = rand() % range;

    return inlineIndex;
}

void YoneticiListesi::removeAt(int index) {
    if (index < 0 || index >= size) throw "Index out of Range";
    YoneticiDugum *del;
    if (index == 0) {
        del = head;
        head = head->sonraki;
        if (head != NULL) head->onceki = NULL;
    } else {
        YoneticiDugum *prv = FindPreviousByPosition(index);
        del = prv->sonraki;
        prv->sonraki = del->sonraki;
        if (del->sonraki != NULL)
            del->sonraki->onceki = prv;
    }
    size--;
    delete del;
}

void YoneticiListesi::moveDugum(int from, int to)throw (IndexOutOfBounds) {
    if (from < 0 || from >= size) throw IndexOutOfBounds("index out of bound");
    YoneticiDugum *del;
    if (from == 0) {
        del = head;
        head = head->sonraki;
        if (head != NULL) head->onceki = NULL;
    } else {
        YoneticiDugum *prv = FindPreviousByPosition(from);
        del = prv->sonraki;
        prv->sonraki = del->sonraki;
        if (del->sonraki != NULL)
            del->sonraki->onceki = prv;
    }
    size--;
    if (to < 0 || to > size) throw "Index out of Range";
    if (to == 0) {

        del->sonraki = head;
        del->onceki = NULL;
        head = del;
        if (head->sonraki != NULL) head->sonraki->onceki = head;
    } else {
        YoneticiDugum *prv = FindPreviousByPosition(to);

        del->sonraki = prv->sonraki;
        del->onceki = prv;
        prv->sonraki = del;
        if (prv->sonraki->sonraki != NULL)
            prv->sonraki->sonraki->onceki = prv->sonraki;
    }
    size++;
}

bool YoneticiListesi::find(SatirListesi*& item) {
    for (YoneticiDugum *itr = head; itr != NULL; itr = itr->sonraki) {
        if (itr->veri == item) return true;
    }
    return false;
}

void YoneticiListesi::reverse() {
    for (YoneticiDugum *itr = head; itr != NULL;) {
        YoneticiDugum *tmp = itr->sonraki;
        itr->sonraki = itr->onceki;
        itr->onceki = tmp;
        if (tmp == NULL) {
            head = itr;
            break;
        }
        itr = tmp;
    }
}

void YoneticiListesi::sortByAverage() {
    if (this->size <= 1)
        return;

    for (int step = 0; step < size; ++step) {


        for (int i = 0; i < size - step - 1; ++i) {
            YoneticiDugum *tmp = this->FindPosition(i);
            YoneticiDugum *tmp2 = tmp->sonraki;

            if (tmp->ort > tmp2->ort) {


                this->moveDugum(i + 1, i);
            }
        }
    }

}

SatirListesi*& YoneticiListesi::elementAt(int index)throw (NoSuchElement) {
    if (index < 0 || index >= size) throw NoSuchElement("No Such Element");
    if (index == 0) return head->veri;
    return FindPreviousByPosition(index)->sonraki->veri;
}

void YoneticiListesi::clear() {
    while (!isEmpty())
        removeAt(0);
}

void YoneticiListesi::yazdirIndex(int index, int x, int y) {
    YoneticiDugum *dugum = this->FindPosition(index);
    ConsolePosition.gotoxy(x, y);
    cout << fixed << setprecision(2);
    cout << dugum << "\n";
    ConsolePosition.gotoxy(x, y + 1);
    cout << "-----------\n";
    ConsolePosition.gotoxy(x, y + 2);
    cout << "|" << dugum->onceki << setw(3) << "|\n";
    ConsolePosition.gotoxy(x, y + 3);
    cout << "-----------\n";
    ConsolePosition.gotoxy(x, y + 4);
    cout << "|" << setw(3) << dugum->ort << setw(5) << "|" << endl;
    ConsolePosition.gotoxy(x, y + 5);
    cout << "-----------\n";
    ConsolePosition.gotoxy(x, y + 6);
    cout << "|" << dugum->sonraki << setw(3) << "|\n";
    ConsolePosition.gotoxy(x, y + 7);
    cout << "-----------\n\n";

}

YoneticiListesi::~YoneticiListesi() {
    clear();
}