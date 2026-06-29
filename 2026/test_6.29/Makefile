CC=g++
BIN=code
#SRC=$(shell ls *.c)
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
RM=rm -f

$(BIN):$(OBJ)
	$(CC) -o $@ $^ 
#%.o:%.c
#	$(CC) -c $<

$(OBJ):$(SRC)
	$(CC) -c $^

.PHONY:
clean:
	$(RM) $(BIN) $(OBJ)


	
