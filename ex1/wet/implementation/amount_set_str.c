#include "amount_set_str.h"
#include <stdio.h>
#include <assert.h>

#include <malloc.h>
//set is an array

typedef struct node{
    char* name;
    double amount;
    struct node * next;
}node;

struct AmountSet_t {
    int size;
    node first;
    int iterator;
};

AmountSet asCreate(){
    AmountSet set = malloc(sizeof (*set));
    if(set == NULL){
        return NULL;
    }
    set->first = NULL;
    set->amount_array = NULL;
    //in add we will check if size =0 and set elements and amount array
    set->iterator = 0;
    set->size = 0;
    return set;
}

void asDestroy(AmountSet set) {
    if (set == NULL)
        return;
    double *outAmount;
    while (asGetAmount(set, set->elements, outAmount)) {
        asDelete(set, asGetFirst(set));
    }
    free(set->elements);
    free(set->amount_array);
    free(set);
}
AmountSet asCopy(AmountSet set){//iterator isn't copied
    if(set == NULL)
        return -1;
    AmountSet ans = asCreate();
    if(set->size == 0){
        return  ans;
    }
    //maybe iterator should be copied here
    ans->size = set->size;
    ans->elements = malloc(*(ans->elements))
    for (int i = 0; i < set->size; ++i) {

    }

}

//for quick tests
int main() {
    printf("Hello, World!\n");
    return 0;
}
