#include "amount_set_str_tests.h"
#include "../matamikya.h"
#include "../amount_set_str.h"
#include "amount_set_str_test_utilities.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
/*
*#define INVENTORY_OUT_FILE "tests/printed_inventory.txt"
*#define INVENTORY_TEST_FILE "tests/expected_inventory.txt"
*#define ORDER_OUT_FILE "tests/printed_order.txt"
*#define ORDER_TEST_FILE "tests/expected_order.txt"
*#define BEST_SELLING_OUT_FILE "tests/printed_best_selling.txt"
*#define NO_SELLING_OUT_FILE "tests/printed_no_selling.txt"
*#define NO_SELLING_TEST_FILE "tests/expected_no_selling.txt"
*#define BEST_SELLING_TEST_FILE "tests/expected_best_selling.txt"
*/
#define ASSERT_OR_DESTROY(expr) ASSERT_TEST_WITH_FREE((expr), matamikyaDestroy(mtm))


bool testCreate() {
    AmountSet am = asCreate();
    ASSERT_TEST(am != NULL);
    asDestroy(am);
    return true;
}

bool testDestroy() {
    AmountSet am = asCreate();
    asDestroy(am);
    /* try to elicit undefined behavior in case matamikyaDestroy has bugs */
    AmountSet mtm2 = asCreate();
    ASSERT_TEST(mtm2 != NULL);
    asDestroy(mtm2);
    return true;
}
bool testCheckSort(){
    AmountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"c")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"bb")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"ba")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"z")== AS_SUCCESS);
    ASSERT_TEST(asRegister(as,"a")== AS_ITEM_ALREADY_EXISTS);

    ASSERT_TEST(0==strcmp(asGetFirst(as),"a"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"ba"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"bb"));
    ASSERT_TEST(strcmp(asGetNext(as),"c"));
    ASSERT_TEST(strcmp(asGetNext(as),"z"));
    ASSERT_TEST(asDelete(as,"bb") == AS_SUCCESS);

    ASSERT_TEST(0==strcmp(asGetFirst(as),"a"));
    ASSERT_TEST(0==strcmp(asGetNext(as),"ba"));
    ASSERT_TEST(strcmp(asGetNext(as),"c"));
    ASSERT_TEST(strcmp(asGetNext(as),"z"));
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
    mountSet as = asCreate();
    ASSERT_TEST(asRegister(as,"a")== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(as,"yosi",1.5)== AS_ITEM_DOES_NOT_EXIST);
    ASSERT_TEST(asChangeAmount(as,"a",1.5)== AS_SUCCESS);
    ASSERT_TEST(asChangeAmount(as,"a",-1.56)== AS_INSUFFICIENT_AMOUNT);
    ASSERT_TEST(asChangeAmount(as,"a",-1.5)== AS_SUCCESS);
    asDestroy(as);
    return true;

}
/*
static MtmProductData copyDouble(MtmProductData number) {
    double *copy = malloc(sizeof(*copy));
    if (copy) {
        *copy = *(double*)number;
    }
    return copy;
}

static void freeDouble(MtmProductData number) {
    free(number);
}

static double simplePrice(MtmProductData basePrice, const double amount) {
    return (*(double*)basePrice) * amount;
}

static double buy10Get10ForFree(MtmProductData basePrice, const double amount) {
    double realAmount = amount;
    if (amount >= 20) {
        realAmount -= 10;
    } else if (amount >= 10) {
        realAmount = 10;
    }
    return simplePrice(basePrice, realAmount);
}

bool testModifyProducts() {
    Matamikya mtm = matamikyaCreate();
    double basePrice = 8.9;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5.8;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, buy10Get10ForFree));
    basePrice = 2000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));
    basePrice = 5000;
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 11, "Television", 4, MATAMIKYA_INTEGER_AMOUNT,
                                    &basePrice, copyDouble, freeDouble, simplePrice));

    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmClearProduct(mtm, 6));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm, 4, 30.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmChangeProductAmount(mtm, 4, -12.85));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT == mtmChangeProductAmount(mtm, 10, 2.25));
    ASSERT_OR_DESTROY(MATAMIKYA_INSUFFICIENT_AMOUNT == mtmChangeProductAmount(mtm, 10, -1000));

    basePrice = 18.5;
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
                      mtmNewProduct(mtm, 7, "Watermelon", 24.54,
                                    MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice, copyDouble,
                                    freeDouble, simplePrice));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmNewProduct(mtm, 7, "Watermelon", 24.5,
                                    MATAMIKYA_HALF_INTEGER_AMOUNT,
                                    &basePrice, copyDouble,
                                    freeDouble, simplePrice));

    matamikyaDestroy(mtm);
    return true;
}

static void makeInventory(Matamikya mtm) {
    double basePrice = 8.9;
    mtmNewProduct(mtm, 4, "Tomato", 2019.11, MATAMIKYA_ANY_AMOUNT, &basePrice, copyDouble,
                  freeDouble, simplePrice);
    basePrice = 5.8;
    mtmNewProduct(mtm, 6, "Onion", 1789.75, MATAMIKYA_ANY_AMOUNT, &basePrice, copyDouble,
                  freeDouble, buy10Get10ForFree);
    basePrice = 2000;
    mtmNewProduct(mtm, 10, "Television", 15, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
    basePrice = 5000;
    mtmNewProduct(mtm, 11, "Smart TV", 4, MATAMIKYA_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
    basePrice = 18.5;
    mtmNewProduct(mtm, 7, "Watermelon", 24.5, MATAMIKYA_HALF_INTEGER_AMOUNT, &basePrice,
                  copyDouble, freeDouble, simplePrice);
}

bool testModifyOrders() {
    Matamikya mtm = matamikyaCreate();
    makeInventory(mtm);

    unsigned int order1 = mtmCreateNewOrder(mtm);
    ASSERT_OR_DESTROY(order1 > 0);
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order1, 11, 1.0));
    ASSERT_OR_DESTROY(MATAMIKYA_PRODUCT_NOT_EXIST ==
                      mtmChangeProductAmountInOrder(mtm, order1, 15, 1.0));
    ASSERT_OR_DESTROY(MATAMIKYA_INVALID_AMOUNT ==
                      mtmChangeProductAmountInOrder(mtm, order1, 11, 1.2));

    unsigned int order2 = mtmCreateNewOrder(mtm);
    ASSERT_OR_DESTROY(order2 > 0);
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 6, 10.25));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 7, 1.5));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmCancelOrder(mtm, order1));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS ==
                      mtmChangeProductAmountInOrder(mtm, order2, 10, 2.0));
    ASSERT_OR_DESTROY(MATAMIKYA_SUCCESS == mtmShipOrder(mtm, order2));

    matamikyaDestroy(mtm);
    return true;
}

static bool fileEqual(FILE *file1, FILE *file2) {
    int c1, c2;
    do {
        c1 = fgetc(file1);
        c2 = fgetc(file2);
    } while (c1 != EOF && c2 != EOF && c1 == c2);
    return (c1 == EOF && c2 == EOF);
}

static bool wholeFileEqual(const char *filename1, const char *filename2) {
    FILE *file1 = fopen(filename1, "r");
    FILE *file2 = fopen(filename2, "r");
    assert(file1);
    assert(file2);
    bool result = fileEqual(file1, file2);
    fclose(file1);
    fclose(file2);
    return result;
}

bool testPrintInventory() {
    Matamikya mtm = matamikyaCreate();
    makeInventory(mtm);
    FILE *outputFile = fopen(INVENTORY_OUT_FILE, "w");
    assert(outputFile);
    ASSERT_OR_DESTROY(mtmPrintInventory(mtm, outputFile) == MATAMIKYA_SUCCESS);
    fclose(outputFile);
    ASSERT_OR_DESTROY(wholeFileEqual(INVENTORY_TEST_FILE, INVENTORY_OUT_FILE));
    matamikyaDestroy(mtm);
    return true;
}
*/