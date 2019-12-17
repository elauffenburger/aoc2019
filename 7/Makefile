CC 		= g++
CCFLAGS	= -Wall -std=c++17
SRC 	= $(wildcard *.cpp)
OBJ		= $(patsubst %.cpp,%.o,$(SRC))
DEPS	= helpers.h types.h instr.h vm.h problem_helpers.h
TRASH	= $(wildcard *.o) $(wildcard *.gch) main

.PHONY: all debug debugc clean

all: main

debug: CCFLAGS += -D DEBUG -g
debug: main

debugc: CCFLAGS += -D DEBUG -D DEBUG_CURSOR -g
debugc: main

main: $(OBJ)
	$(CC) $(CCFLAGS) -o main $(OBJ)

%.o: %.cpp 
	$(CC) $(CCFLAGS) -c $^

clean:
	rm -f $(TRASH)