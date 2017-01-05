CPPFLAGS = -Wall -Wno-unused-result -ansi -O2 -pedantic -g -fopenmp

shared: shared.o
	g++ $(CPPFLAGS) shared.o -o shared

shared.o: shared.cpp
	g++ $(CPPFLAGS) -c shared.cpp

clean:
	rm shared
