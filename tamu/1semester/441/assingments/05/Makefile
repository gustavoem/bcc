FLAGS = -O2 -g -Wall -fmessage-length=0 -lglut -lGL -lGLU

OBJS = Cube.o 

TARGET = main

$(TARGET): main.o $(OBJS)
	g++ -o $(TARGET) main.o $(OBJS) $(FLAGS)

main.o: main.cpp
	g++ -c -o main.o main.cpp $(FLAGS)

all:	$(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
