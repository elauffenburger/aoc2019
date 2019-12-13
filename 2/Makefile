CC 		= g++
CFLAGS	= -Wall -fpermissive
SRC 	= $(wildcard *.cpp)
OBJ		= $(patsubst %.cpp,%.o,$(SRC))
DEPS	= main.h helpers.h
TRASH	= $(wildcard *.o) $(wildcard *.gch) main

.PHONY: all clean
all: main

main: main.o
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.cpp helpers.cpp $(DEPS)
	$(CC) $(CFLAGS) -c main.cpp helpers.cpp $(DEPS)

clean:
	rm -f $(TRASH)