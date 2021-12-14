CC = gcc
OBJ = matamikya.o  matamikya_tests.o matamikya_main.o #libas.a libmtm.a
EXEC = prog
DEBUG_FLAG = -L. -lmtm -lm -las
C_FLAG = -g
COMP_FLAG = -std=c99 -Werror -Wall -pedantic-errors

$(EXEC) : $(OBJ)
	$(CC) $(DEBUG_FLAG) $(COMP_FLAG) -o $@
matamikya.o : matamikya.c matamikya.h set.h list.h amount_set.h
	$(CC) $(C_FLAG) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJ) $(EXEC)

