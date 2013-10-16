COMPILER = c++
FLAGS = -Wall -std=c++11

main.x : main.o libintegrate.a
	$(COMPILER) $(FLAGS) $< -L. -lintegrate -o $@

%.o : %.cpp simpson.hpp
	$(COMPILER) -c $(FLAGS) $< 

libintegrate.a : simpson.o
	ar ruc $@ $^
