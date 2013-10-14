COMPILER = c++
FLAGS = -Wall -std=c++11
PYTHON = python

plot.pdf : plot.py output.txt
	$(PYTHON) $<

output.txt : benchmark.x
	./benchmark.x

benchmark.x : benchmark.o simpsonsquare.o 
	$(COMPILER) $(FLAGS) $^ -o $@

%.o : %.cpp simpsonsquare.hpp ../timer/dg_timer.hpp
	$(COMPILER) $(FLAGS) -c $< 

clean : 
	rm plot.pdf output.txt benchmark.x benchmark.o

.PHONY : clean

.SECONDARY : output.txt

.IGNORE : clean
