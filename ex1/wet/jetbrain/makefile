CC = gcc
OBJ = matamikya.o  matamikya_tests.o #libas.a libmtm.a
EXEC = prog
DEBUG_FLAG = -lm -L. -las -lm
COMP_FLAG = -std=c99 -Werror -Wall -pedantic-errors

$(EXEC) : $(OBJ)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -o $@
matamikya_tests.o : tests/
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -c $*.c
matamikya.o : matamikya.c matamikya.h set.h list.h amount_set.h
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJ) $(EXEC)

