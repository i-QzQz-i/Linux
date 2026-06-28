BIN=test
CC=g++
SRC=test.cpp
OBJ=test.o
LFLAGS=-o
FLAGS=-c
RM=rm -f

$(BIN):$(OBJ)
	@$(CC) $(LFLAGS) $@ $^
	@echo "linking $^ to $@"
$(OBJ):$(SRC)
	@$(CC) $(FLAGS) $^

.PHONY:clean
clean:
	$(RM) $(OBJ) $(BIN)

.PHONY:text
text:
	@echo $(BIN)
	@echo $(CC)
	@echo $(SRC)
	@echo $(OBJ)
	echo  $(RM)






#test:test.o
#	$(CC) -o $(BIN) $^
#test.o:test.s
#	$(CC) -o $@ -c $^
#test.s:test.i
#	$(CC) -o $@ -S $^
#test.i:test.cpp
#	$(CC) -o $@ -E $^
#
#.PHONY:clean
#clean:
#	$(RM) *.i *.s *.o $(BIN)
