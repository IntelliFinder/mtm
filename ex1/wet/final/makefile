CC=gcc
OBJS = matamikya.o matamikya_order.o matamikya_product.o matamikya_print.o tests/matamikya_main.o tests/matamikya_tests.o
OBJSAS = amount_set_str.o amount_set_str_element.o amount_set_str_main.o amount_set_str_tests.o 
EXEC = matamikya
EXECAS= amount_set_str 
# OBJ=mtmiya.o
DEBUG = -g -DNDEBUG# now empty, assign -g for debug
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror

$(EXEC) : $(OBJS)
	$(CC) $(CFLAGS)  $(DEBUG) $(OBJS) -o $@ -L. -lmtm -lm -las

# $(OBJ): $(OBJS)
# 	ld -r -o $(OBJ) $(OBJS)

$(EXECAS) : $(OBJSAS)
	$(CC) $(CFLAGS)  $(DEBUG) $(OBJSAS)  -o $@
amount_set_str.o: amount_set_str.c amount_set_str.h \
 amount_set_str_element.c
amount_set_str_element.o: amount_set_str_element.c amount_set_str.h
amount_set_str_main.o: amount_set_str_main.c amount_set_str_tests.h \
 amount_set_str_test_utilities.h
amount_set_str_tests.o: amount_set_str_tests.c amount_set_str_tests.h \
 matamikya.h amount_set_str.h amount_set_str_test_utilities.h
matamikya.o: matamikya.c matamikya.h set.h matamikya_print.h \
 matamikya_order.h matamikya_product.h
matamikya_order.o: matamikya_order.c matamikya.h matamikya_print.h \
 matamikya_order.h set.h matamikya_product.h
matamikya_print.o: matamikya_print.c matamikya_print.h
matamikya_product.o: matamikya_product.c matamikya.h matamikya_product.h \
 set.h matamikya_order.h matamikya_print.h

clean:
	rm -f $(OBJS) $(EXEC) $(OBJSAS) $(EXECAS)