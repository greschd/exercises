main : main.o libintegrate.a
	c++ -Wall -std=c++11 $< -L. -lintegrate -o $@

%.o : %.cpp simpson.hpp.gch 
	c++ -c -Wall -std=c++11 $< 

libintegrate.a : simpson.o
	ar ruc $@ $^

simpson.hpp.gch : simpson.hpp
	c++ -c -Wall -std=c++11 $^
