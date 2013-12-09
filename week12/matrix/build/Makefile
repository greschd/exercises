timings: optima.txt ../main/benchmark.py ../main/blocking.cpp ../main/library.cpp ../main/simple.cpp ../main/main.cpp 
	touch timings
	python -c "execfile('../main/benchmark.py'); measure()"

optima.txt: ../main/benchmark.py ../main/blocking.cpp ../main/main.cpp
	python -c "execfile('../main/benchmark.py'); tune()"
