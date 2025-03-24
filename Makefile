comp: 
	g++ -std=c++11 -Wall biggest-divisible-conglomerate.cpp main.cpp -o bdc

run: 
	./bdc

all: comp run
