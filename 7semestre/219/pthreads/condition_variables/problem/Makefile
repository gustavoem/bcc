OUTPUT = basic_problem
CC = gcc
CFLAGS = -Wall -Wno-unused-result -ansi -O0 -pedantic -g
PTFLAG = -pthread

.PHONY: all
	all: $(OUTPUT)

$(OUTPUT): $(OUTPUT).c
	$(CC) -o $(OUTPUT) $(CFLAGS) $(PTFLAG) $(OUTPUT).c

.PHONY: clean

echo:
	echo $(OUTPUT) $(CC) $(CFLAGS) $(PTFLAGS)

clean:
	rm $(OUTPUT)

