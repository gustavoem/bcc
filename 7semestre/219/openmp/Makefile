CPPFLAGS = -Wall -Wno-unused-result -ansi -O2 -pedantic -g -fopenmp

minimum: minimum.o
	g++ $(CPPFLAGS) minimum.o -o minimum

minimum.o: minimum.cpp
	g++ $(CPPFLAGS) -c minimum.cpp

clean:
	rm minimum
