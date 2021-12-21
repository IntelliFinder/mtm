#include "amount_set_str.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#define FIRST_NAME = "trash"

 struct AmountSet_t {
    char* name;
    double amount;
    struct AmountSet_t* next;
    struct AmountSet_t* iterator;
};
