all: compile run

compile:
	g++ -I ./include/ -o ./lib/DNA.o -c ./src/DNA.cpp
	g++ -I ./include/ -o ./lib/Chromosome.o -c ./src/Chromosome.cpp
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	
	g++ -I ./include/ -o ./bin/main ./lib/DNA.o ./lib/Chromosome.o ./lib/Node.o ./src/main.cpp
	
run:
	./bin/main