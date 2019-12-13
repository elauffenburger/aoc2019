CC 		= g++
CCFLAGS	= -Wall -fpermissive
SRC 	= $(wildcard *.cpp)
OBJ		= $(patsubst %.cpp,%.o,$(SRC))
DEPS	= helpers.h types.h
TRASH	= $(wildcard *.o) $(wildcard *.gch) main

.PHONY: all debug debugc clean

all: main

debug: CCFLAGS += -D DEBUG -g
debug: main

debugc: CCFLAGS += -D DEBUG -D DEBUG_CURSOR -g
debugc: main

main: main.o
	$(CC) $(CCFLAGS) -o main $(OBJ)

main.o: main.cpp helpers.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c main.cpp helpers.cpp $(DEPS)

clean:
	rm -f $(TRASH)