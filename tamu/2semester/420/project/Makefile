CXXFLAGS = -O2 -g -Wall -std=c++14 

OBJS = ToffoliGate.o Multiplier.o GAMultiplier.o LBMultiplier.o GeneticAlgorithm.o LocalBeam.o PrimeList.o BitEntropy.o

TARGET = main

$(TARGET): main.o $(OBJS)
	g++  $(FLAGS) -o $(TARGET) main.o $(OBJS)

main.o: main.cpp
	g++ $(FLAGS) -c -o main.o main.cpp 

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
