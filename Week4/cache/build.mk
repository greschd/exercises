COMPILER = c++
FLAGS = -Wall -std=c++11 
PYTHON = python

#adding a phony dependency 

allplots : plot-1.pdf plot-2.pdf plot-3.pdf plot-4.pdf plot-5.pdf plot-6.pdf plot-7.pdf plot-8.pdf  
.SECONDARY : output-1.txt output-2.txt output-3.txt output-4.txt output-5.txt output-6.txt output-7.txt output-8.txt  

plot-%.pdf : plot-%.py output-%.txt
	$(PYTHON) $<

output-%.txt : var-%.txt cache.x
	./cache.x < $<

cache.x : cache.o arrayloop.o 
	$(COMPILER) $(FLAGS) $^ -o $@

%.o : %.cpp arrayloop.hpp 
	$(COMPILER) -c $(FLAGS) $<

clean : 
	rm output-*.txt
	rm plot-*.pdf

.PHONY: clean
