CC = gcc
OBJ = amount_set_str.o
EXEC = prog
DEBUG_FLAG = -DNDEBUG
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror

$(EXEC) : $(OBJ)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -o $@
amount_set_str.o : amount_set_str.c amount_set_str.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJ) $(EXEC)
