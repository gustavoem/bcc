FLAGS = -O2 -g -Wall -fmessage-length=0 -lglut -lGL -lGLU

OBJS =	Polygon.o \

TARGET = ScanConvert

$(TARGET): ScanConvert.o $(OBJS)
	g++ -o $(TARGET) ScanConvert.o $(OBJS) $(FLAGS)

ScanConvert.o: ScanConvert.cpp
	g++ -c -o ScanConvert.o ScanConvert.cpp $(FLAGS)

all:	$(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)
