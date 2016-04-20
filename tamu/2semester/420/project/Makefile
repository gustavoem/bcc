FLAGS = -g -O2 -Wall -pedantic -std=c++14 

OBJS = ToffoliGate.o Multiplier.o GAMultiplier.o GeneticAlgorithm.o

TARGET = main

$(TARGET): main.o $(OBJS)
	g++ -o $(TARGET) main.o $(OBJS) $(FLAGS)

main.o: main.cpp
	g++ -c -o main.o main.cpp $(FLAGS)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
