COMPILER = c++
FLAGS = -Wall -std=c++11

benchmark.x : benchmark.o simpsonsquare.o 
	$(COMPILER) $(FLAGS) $< simpsonsquare.o -o $@

%.o : %.cpp simpsonsquare.hpp dg_timer.hpp inputtovector.hpp 
	$(COMPILER) -c  $(FLAGS) $<
