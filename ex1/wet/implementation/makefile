#CC = gcc
#OBJ = matamikya.o
#EXEC = prog
#DEBUG_FLAG = -DNDEBUG
#COMP_FLAG = -L. -lmtm -lm -las -std=c99 -Wall -pedantic-errors -Werror
#
#$(EXEC) : $(OBJ)
#	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) -o $^
#matamikya.o : matamikya_main.c matamikya_tests.c matamikya.c  matamikya_tests.h test_utilities.h  matamikya.h
#	$(CC) $(COMP_FLAG) $(DEBUG_FLAG) -c matamikya_main.c matamikya_tests.c matamikya.c
#clean:
#	rm -f $(OBJ) $(EXEC)
#
matamikya : matamikya.c tests/matamikya_main.c tests/matamikya_tests.c
	gcc -std=c99 -Wall -pedantic-errors -Werror -o matamikya matamikya.c tests/matamikya_main.c tests/matamikya_tests.c -L. -lmtm -lm -las
#gcc -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG -o matamikya matamikya*.c tests/matamikya*.c  -L. -lmtm -lm -las
