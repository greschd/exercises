main : main.o libintegrate.a
	c++ -Wall -std=c++11 $< -L. -lintegrate -o $@

%.o : %.cpp %.hpp.gtc
	c++ -c -Wall -std=c++11 $< 

libintegrate.a : simpson.o
	ar ruc $@ $^

simpson.hpp.gtc : simpson.hpp
	c++ -Wall -std=c++11 $<
