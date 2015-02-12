all: epot.pdf ekin.pdf

*.pdf: main.py data.txt
	python3 main.py

data.txt: pimc.out
	rm -f data.txt
	./pimc.out

pimc.out: pimc.cpp
	g++ -Wall -std=c++11 -O3 -march=core2 -m64 -o pimc.out pimc.cpp
