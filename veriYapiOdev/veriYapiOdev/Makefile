all: build run


build:
	g++ -I ./include/ -o ./lib/ConsoldaGoruntule.o -c ./src/ConsoldaGoruntule.cpp
	g++ -I ./include/ -o ./lib/Exception.o -c ./src/Exception.cpp
	g++ -I ./include/ -o ./lib/DosyaOku.o -c ./src/DosyaOku.cpp
	g++ -I ./include/ -o ./lib/SatirListesi.o -c ./src/SatirListesi.cpp
	g++ -I ./include/ -o ./lib/SatirListesiDugum.o -c ./src/SatirListesiDugum.cpp
	g++ -I ./include/ -o ./lib/YoneticiListesi.o -c ./src/YoneticiListesi.cpp
	g++ -I ./include/ -o ./lib/YoneticiDugum.o -c ./src/YoneticiDugum.cpp

	g++ -I ./include/ -o ./bin/main ./lib/ConsoldaGoruntule.o ./lib/Exception.o ./lib/DosyaOku.o ./lib/SatirListesi.o ./lib/SatirListesiDugum.o ./lib/YoneticiListesi.o  ./lib/YoneticiDugum.o   ./src/main.cpp

calistir:
	./bin/main
	