#include "amount_set_str.h"
#include <stdio.h>
#include <assert.h>

#include <malloc.h>
#include <string.h>
//set is an array
#define FIRST_NAME = "trash"

typedef struct AmountSet_t {
    char* name;
    double amount;
    struct AmountSet_t* next;
    struct AmountSet_t* iterator;
}*AmountSet;

AmountSet asCreate(){
    AmountSet set = malloc(sizeof (*set));
    if(set == NULL){
        return NULL;
    }
    set->name = malloc(sizeof *(set->name));
    //no need to actually set a real name for first
    set->amount = 0;
    //in add we will check if size =0 and set elements and amount array
    set->iterator = NULL;
    set->next = NULL;
    return set;
}

void asDestroy(AmountSet set) {
    if (set == NULL)
        return;

    while (asGetSize(set)) {
        asDelete(set, asGetFirst(set));
    }
    free(set->name);
    free(set);
}
AmountSet asCopy(AmountSet set){//iterator isn't copied
    if(set == NULL)
        return -1;
    AmountSet ans = asCreate();
    assert(ans != NULL);
    if(ans == NULL)
        return NULL;
    //maybe iterator should be copied here
    AmountSet setRun = set->next;//remember that first is trash

    AmountSet ansRun = ans;
    while(setRun != NULL){
        ansRun->next = malloc(sizeof (*ansRun->next));
        assert(ansRun->next != NULL);
        if(ansRun->next == NULL)
            return NULL;

        ansRun = ansRun->next;
        ansRun->name = malloc(sizeof (char)* (1+strlen(setRun->name)));
        assert(ansRun->name != NULL);
        if(ansRun->name == NULL)
            return NULL;

        strcpy(ansRun->name,set->name);
        setRun = setRun->next;
    }
    return ans;
}

int asGetSize(AmountSet set){
    if(set == NULL)
        return -1;
    int ans = 0;
    AmountSet setRun = set->next;
    while (setRun != NULL){
        ans++;
        setRun = setRun->next;
    }
    return ans;
}

bool asContains(AmountSet set, const char* element){
    if(set == NULL || element == NULL)
        return false;
    AmountSet setRun = set->next;
    while (setRun != NULL){
        if(0==strcmp(setRun->name,element))
            return true;
        setRun = setRun->next;
    }
    return false;
}

char* asGetNext(AmountSet set)
{
    if( set->iterator == NULL )
        return NULL;
    AmountSet current_set = set->iterator;
    AmoountSet next = current_set->next;
    return next->name;
}
char* asGetFirst(AmountSet set)
{
    if( set == NULL )
        return NULL;
    AmountSet viable = set->next;
    return viable->name;
}
AmountSetResult asClear(AmountSet set)
{
    if( set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    AmountSet iter = set->next;
    free(set);
    while( iter != NULL )
    {
        set = iter;
        iter = set->next;
        free(set);
    }

    return AS_SUCCESS;
}

//for quick tests
int main() {
    printf("Hello, World!\n");
    return 0;
}
