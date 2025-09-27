all: compile run

compile:
	gcc -I ./include/ -o ./lib/Gezegen.o -c ./src/Gezegen.c
	gcc -I ./include/ -o ./lib/KayacGezegen.o -c ./src/KayacGezegen.c
	gcc -I ./include/ -o ./lib/GazDeviGezegen.o -c ./src/GazDeviGezegen.c
	gcc -I ./include/ -o ./lib/CuceGezegen.o -c ./src/CuceGezegen.c
	gcc -I ./include/ -o ./lib/BuzDeviGezegen.o -c ./src/BuzDeviGezegen.c
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c
	gcc -I ./include/ -o ./lib/UzayAraci.o -c ./src/UzayAraci.c
	gcc -I ./include/ -o ./lib/ZamanHesaplama.o -c ./src/ZamanHesaplama.c
	gcc -I ./include/ -o ./lib/DosyaOkuma.o -c ./src/DosyaOkuma.c
	gcc -I ./include/ -o ./bin/Simulasyon ./lib/Gezegen.o ./lib/KayacGezegen.o ./lib/GazDeviGezegen.o ./lib/CuceGezegen.o ./lib/BuzDeviGezegen.o ./lib/Kisi.o ./lib/UzayAraci.o ./lib/ZamanHesaplama.o ./lib/DosyaOkuma.o ./src/Simulasyon.c


run:
	./bin/Simulasyon