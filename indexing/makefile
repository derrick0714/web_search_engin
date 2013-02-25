CC     = g++
CFLAGS = -Wall -Wextra -g -DLexic_Compare -DTwo_Options


# program name 
PROG = hello

# bin directory
BIN = ./bin

# source directory
SRC = ./src

# target (merge with bin and name)
TARGET = $(BIN)/$(PROG)

OBJ = $(SRC)/*.o

CPPS = $(SRC)/*.cpp


%.o : %.cpp
	$(CXX) $(SRC) -o $@ -c $<
% : %.o
	$(CXX) -o $@ $^ $(SRC)

all: $(CPPS) $(TARGET)
#main.o: main.cpp
#	g++ -c main.cpp
