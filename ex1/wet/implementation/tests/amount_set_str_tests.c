#include "amount_set_str_tests.h"
#include "../matamikya.h"
#include "../amount_set_str.h"
#include "amount_set_str_test_utilities.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_OR_DESTROY(expr) ASSERT_TEST_WITH_FREE((expr), asDestroy(as))


bool testCreate() {
    AmountSet as = asCreate();
    ASSERT_TEST(as != NULL);
    asDestroy(as);
    return true;
}

bool testDestroy() {
    AmountSet as = asCreate();
    asDestroy(as);
    /* try to elicit undefined behavior in case matamikyaDestroy has bugs */
    AmountSet mtm2 = asCreate();
    ASSERT_TEST(mtm2 != NULL);
    asDestroy(mtm2);
    return true;
}
bool testCheckSort(){
    //also checks iterators's state
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"c")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"bb")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"ba")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"z")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"a")== AS_ITEM_ALREADY_EXISTS);

    ASSERT_TEST(0==strcmp(asGetFirst(as),"a"));
    ASSERT_TEST(5== asGetSize(as));
    ASSERT_TEST(0==strcmp(asGetNext(as),"ba"));
    ASSERT_TEST(asContains(as,"z"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"bb"));
    ASSERT_TEST(asChangeAmount(as,"a",2.4) == AS_SUCCESS);
    ASSERT_TEST(0==strcmp(asGetNext(as),"c"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"z"));
    ASSERT_TEST((asDelete(as,"bb") == AS_SUCCESS));

    ASSERT_TEST(0==strcmp(asGetFirst(as),"a"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"ba"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"c"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"z"));
    asDestroy(as);
    return true;
}
bool testCheckCopy() {
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"yosi") == AS_SUCCESS);

    AmountSet cpy = asCopy(as);
    ASSERT_TEST(asRegister(as,"moshe")== AS_SUCCESS);

    ASSERT_TEST(asChangeAmount(as,"moshe",2.5)== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(as,"yosi",1.5)== AS_SUCCESS);
    ASSERT_TEST(asGetSize(cpy) == 1);
    ASSERT_TEST(asContains(cpy,"yosi") == true);
    ASSERT_TEST(asContains(cpy,"moshe") == false);
    double firstAmount;
    char* first = asGetFirst(as);
    if (asGetAmount(as, first, &firstAmount) == AS_SUCCESS) {
        ASSERT_TEST(firstAmount == 2.5);
    } else
        return false;
    ASSERT_TEST(asGetSize(as) == 2);
    ASSERT_TEST(0== strcmp("yosi",asGetNext(as)));//checked iterator's state
    ASSERT_TEST(asDelete(as,"moshe") == AS_SUCCESS);
    ASSERT_TEST(asGetSize(as)== 1);
    asDestroy(cpy);
    asDestroy(as);
    return true;
}
bool testCheckClear() {
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asClear(as) == AS_SUCCESS);
    ASSERT_TEST(asGetSize(as) == 0);
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asGetSize(as) == 1);
    asDestroy(as);
    return true;
}
bool testCheckChangeAmount() {
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(as,"yosi",1.5)== AS_ITEM_DOES_NOT_EXIST);
    ASSERT_TEST(asChangeAmount(as,"a",1.5)== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(as,"a",-1.56)== AS_INSUFFICIENT_AMOUNT);
    ASSERT_TEST(asChangeAmount(as,"a",-1.5)== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(NULL,"b",1)== AS_NULL_ARGUMENT );
    asDestroy(as);
    return true;

}
bool testCheckIterator(){
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"hello")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"world")== AS_SUCCESS);
    ASSERT_TEST(asGetFirst(as)== AS_SUCCESS);
    ASSERT_TEST(strcmp(asGetFirst(as), "hello")==0);
    asDestroy(as);
    return true;

}