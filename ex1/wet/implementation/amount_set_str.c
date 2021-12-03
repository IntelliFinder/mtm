#include "amount_set_str.h"
#include <stdio.h>
#include <assert.h>

#include <malloc.h>

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
        return NULL;
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

AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    AmountSet ph = set;
    while( ph!=NULL )
    {
        if( *(ph->name) == *element )
        {
            return AS_ITEM_ALREADY_EXISTS;
        }
        ph=ph->next;
    }
    AmountSet new = asCreate();
    *(new) = { element, 0, set->next , NULL};
    set->next = new;
    return AS_SUCCESS;
}
AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount)
{
    if( element == NULL )
    {
        return AS_NULL_ARGUMENT;
    }
    if( set== NULL )
    {
        return AS_NULL_ARGUMENT;
    }
    set = set->next;
    while( set != NULL )
    {
        if ( *(set->name) == *element)
        {
            if( set->amount >= amount )
            {
                set->amount -=amount;
            }
            else{
                return AS_INSUFFICIENT_AMOUNT;
            }
        }
        set=set->next;
    }
    return AS_ITEM_DOES_NOT_EXIST;
}

AmountSetResult asDelete(AmountSet set, const char* element)
{
    if( set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    prev = set;
    set = set->next;
    while(set != NULL)
    {
        if( *(set->name) == *element )
        {
            prev->next = set->next;
            free(set);
            return AS_SUCCESS;
        }
        set = set->next;
    }
    return AS_ITEM_DOES_NOT_EXIST
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


//for quick tests
int main() {
    printf("Hello, World!\n");
    return 0;
}
