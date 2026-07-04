#SRC=$(shell ls *.cpp)
SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)
BIN=Process
CC=g++

$(BIN):$(OBJ)
	$(CC) -o $@ $^
%.o:%.cpp	
	$(CC) -c $^

.PHONY:clean 
clean:
	rm -f $(OBJ) $(BIN)
