CPPFLAGS = -O2 -g -lGL -lglut -lGLU 

OBJS =	Polygon.o \

TARGET = main

$(TARGET): ScanConvert.o $(OBJS)
	$(CXX) -o $(TARGET) ScanConvert.o $(OBJS) $(CPPFLAGS)

ScanConvert.o:
	$(CXX) -c -o ScanConvert.cpp

all:	$(TARGET)

clean:
	rm -f *.o
	rm -f $(TEST)
	rm -f $(TARGET)
