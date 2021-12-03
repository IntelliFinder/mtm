#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct AmountSet_t
{
    char* name;
    int amount;
    AmountSet_t next;
}*AmountSet;
typedef enum AmountSetResult_t {
    AS_SUCCESS = 0,
    AS_OUT_OF_MEMORY,
    AS_NULL_ARGUMENT,
    AS_ITEM_ALREADY_EXISTS,
    AS_ITEM_DOES_NOT_EXIST,
    AS_INSUFFICIENT_AMOUNT
} AmountSetResult;
AmountSet asCreate();
void asDestroy(AmountSet set);
AmountSet asCopy(AmountSet set);
int asGetSize(AmountSet set);
bool asContains(AmountSet set, const char* element);
AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount);
AmountSetResult asRegister(AmountSet set, const char* element);
AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount);
AmountSetResult asDelete(AmountSet set, const char* element);
AmountSetResult asClear(AmountSet set);
char* asGetFirst(AmountSet set);
char* asGetNext(AmountSet set);

int main() {

    return 0;

}
