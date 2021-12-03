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
        ans->next = NULL;
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
AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount){
    if(set == NULL || element == NULL || outAmount == NULL)
        return AS_NULL_ARGUMENT;
    if(!asContains(set, element))
        return AS_ITEM_DOES_NOT_EXIST;
    AmountSet run = set->next;
    while (0 != strcmp(run->name,element)){
        assert(run!=NULL);
        run = run->next;
    }
    assert(!strcmp(run->name,element));
    *outAmount = run->amount;
    return AS_SUCCESS;
}
AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set,element))
        return AS_ITEM_ALREADY_EXISTS;
    AmountSet ph = set;
    while(ph->next!=NULL && 0 < strcmp(ph->next->name,element))
    {
        ph=ph->next;
    }
    AmountSet new = malloc(sizeof (*set));
    if(new == NULL){
        return AS_OUT_OF_MEMORY;
    }
    new->name = malloc(sizeof *(set->name) * (strlen(element)+1));
    if(new->name == NULL)
        return AS_OUT_OF_MEMORY;
    strcpy(new->name,element);
    new->amount = 0;
    new->iterator = NULL;
    new->next = ph->next;
    ph ->next = new;
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
        if (0 == strcmp((set->name),element))
        {
            if( set->amount + amount >= 0 )
            {
                set->amount +=amount;
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
    AmountSet prev = set;
    set = set->next;
    while(set != NULL)
    {
        if( strcmp((set->name),element)==0 )
        {
            prev->next = set->next;
            free(set->name);
            free(set);
            return AS_SUCCESS;
        }
        prev = set;
        set = set->next;
    }
    return AS_ITEM_DOES_NOT_EXIST;
}
AmountSetResult asClear(AmountSet set)
{
    if( set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    AmountSet iter = set->next;
    free(set->name);
    free(set);
    while( iter != NULL )
    {
        set = iter;
        iter = set->next;
        free(set->name);
        free(set);
    }

    return AS_SUCCESS;
}
char* asGetNext(AmountSet set)
{
    if( set->iterator == NULL )
        return NULL;
    AmountSet current_set = set->iterator;
    AmountSet next = current_set->next;
    set->iterator = next;
    return next->name;
}
char* asGetFirst(AmountSet set)
{
    if( set == NULL )
        return NULL;
    AmountSet viable = set->next;
    set->iterator = viable;
    return viable->name;

}


//for quick tests
int main() {
    AmountSet as = asCreate();
    asRegister(as,"yosi");

    AmountSet cpy = asCopy(as);
    asRegister(as,"moshe");

    asChangeAmount(as,"moshe",2.5);
    asChangeAmount(as,"yosi",1.5);
    printf("size of cpy %d\n", asGetSize(cpy));
    printf("cpy contains yosi %d\n", asContains(cpy,"yosi"));
    printf("cpy contains moshe %d\n", asContains(cpy,"moshe"));
    double firstAmount;
    char* first = asGetFirst(as);
    if (asGetAmount(as, first, &firstAmount) == AS_SUCCESS) {
        printf("First amount: %f\n", firstAmount);
    }
    printf("size of as %d\n", asGetSize(as));
    asDelete(as,"moshe");
    printf("size of as %d\n", asGetSize(as));

    asDestroy(as);
    return 0;
}
