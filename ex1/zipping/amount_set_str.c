#include "amount_set_str.h"
#include "amount_set_str_element.c"

#include <stdio.h>
#include <assert.h>

#include <malloc.h>
#include <string.h>

#define FIRST_NAME = "trash"

AmountSet asCreate(){
    AmountSet set = malloc(sizeof (*set));
    if(set == NULL){
        return NULL;
    }
    set->name = malloc(sizeof *(set->name));
    if( set->name == NULL ){//allocation failure{
        return NULL;
    }
    //no need to actually set a real name for first
    set->amount = 0;
    set->iterator = NULL;
    set->next = NULL;
    return set;
}

void asDestroy(AmountSet set) {
    if (set == NULL)
    {
        return;
    }
    while (asGetSize(set)) {
        asDelete(set, asGetFirst(set));
    }
    free(set->name);
    free(set);
}
AmountSet asCopy(AmountSet set){//iterator isn't copied
    if(set == NULL){
        return NULL;
    }
    AmountSet ans = asCreate();
    assert(ans != NULL);
    if(ans == NULL){
        return NULL;
    }
    set->iterator = NULL;//iterator undefined after function call
    //maybe iterator should be copied here
    AmountSet setRun = set->next;//remember that first is trash
    AmountSet ansRun = ans;
    while(setRun != NULL){
        ansRun->next = malloc(sizeof (*ansRun->next));
        assert(ansRun->next != NULL);
        if(ansRun->next == NULL){
            return NULL;
        }
        ansRun = ansRun->next;
        ansRun->next = NULL;
        ansRun->name = malloc(sizeof (char)* (1+strlen(setRun->name)));
        assert(ansRun->name != NULL);
        if(ansRun->name == NULL)
        {
            return NULL;
        }

        strcpy(ansRun->name,setRun->name);
        setRun = setRun->next;
    }
    return ans;
}

int asGetSize(AmountSet set){
    if(set == NULL){
        return -1;
    }
    int ans = 0;
    AmountSet setRun = set->next; //first is trash
    while (setRun != NULL){
        ans++;
        setRun = setRun->next;
    }
    return ans;
}

bool asContains(AmountSet set, const char* element){
    if(set == NULL || element == NULL)
    {
        return false;
    }
    AmountSet setRun = set->next;
    while (setRun != NULL){
        if(0==strcmp(setRun->name,element)){
            return true;
        }
        setRun = setRun->next;
    }
    return false;
}
AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount){
    if(set == NULL || element == NULL || outAmount == NULL){
        return AS_NULL_ARGUMENT;
	}
    if(!asContains(set, element)){
        return AS_ITEM_DOES_NOT_EXIST;
	}
    AmountSet run = set->next;
    while (0 != strcmp(run->name,element)){
        assert(run!=NULL);
        run = run->next;
    }
    assert(!strcmp(run->name,element));
    *outAmount = run->amount;
    return AS_SUCCESS;
}
//must be in lexicogrpahic order
AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(set == NULL)
    {
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set,element)){
        return AS_ITEM_ALREADY_EXISTS;
	}
    AmountSet ph = set;
    while(ph->next!=NULL && strcmp((ph->next)->name,element) < 0 )
    {
        ph=ph->next;
    }
    AmountSet new = malloc(sizeof (*set));
    if(new == NULL){
        return AS_OUT_OF_MEMORY;
    }
    new->name = malloc(sizeof *(set->name) * (strlen(element)+1));
    if(new->name == NULL){
        return AS_OUT_OF_MEMORY;
	}
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
                return AS_SUCCESS;
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
    set->next = NULL;
    //free(set->name); we need first Node
    //free(set);
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
    if( set->iterator == NULL ){
        return NULL;
	}
    AmountSet current_set = set->iterator;
    AmountSet next = current_set->next;
    set->iterator = next;
    if(next == NULL){
        return NULL;
	}
    return next->name;
}
char* asGetFirst(AmountSet set)
{
    if( set == NULL ){
        return NULL;
    }
    AmountSet viable = set->next;//first element is trash
    set->iterator = viable;
    return viable->name;

}

void printASResult(AmountSetResult asr){
    switch (asr){
        case AS_SUCCESS:
            printf("AS_SUCCESS\n");
            break;
        case AS_NULL_ARGUMENT:
            printf("AS_NULL_ARGUMENT\n");
            break;
        case AS_ITEM_DOES_NOT_EXIST:
            printf("AS_ITEM_DOES_NOT_EXIST");
            break;
        case AS_OUT_OF_MEMORY:
            printf("AS_OUT_OF_MEMORY");
            break;
        case AS_ITEM_ALREADY_EXISTS:
            printf("AS_ITEM_ALREADY_EXISTS");
            break;
        case AS_INSUFFICIENT_AMOUNT:
            printf("AS_INSUFFICIENT_AMOUNT");
            break;
        default:
            break;
    }

}
