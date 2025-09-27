#ifndef DosyaOku_hpp
#define DosyaOku_hpp

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "SatirListesi.hpp"
#include "YoneticiListesi.hpp"

class DosyaOku {
private:
    std::string fileName;
    int lineCount();
    SatirListesi **lines;
    void readLine();
public:
    DosyaOku(std::string);
    ~DosyaOku();
    YoneticiListesi* GetFillYoneticiListesi();



};

#endif 

