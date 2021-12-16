CC = gcc
#OBJ = matamikya.o libas.a libmtm.a
EXEC = prog
DEBUG_FLAG = -L. -lmtm
COMP_FLAG = -std=c99 -Werror -Wall -pedantic-errors

$(EXEC) :
	$(CC) $(COMP_FLAG) -o matamikya matamikya.c $(DEBUG_FLAG)
clean:
	rm -f $(OBJ) $(EXEC)

