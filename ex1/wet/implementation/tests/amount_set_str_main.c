#include "amount_set_str_tests.h"
#include "amount_set_str_test_utilities.h"

int main()
{
    RUN_TEST(testCreate);
    RUN_TEST(testDestroy);
    RUN_TEST(testCheckSort);
    RUN_TEST(testCheckCopy);
    RUN_TEST(testCheckClear);
    /*
    RUN_TEST(testModifyProducts);
    RUN_TEST(testModifyOrders);
    RUN_TEST(testPrintInventory);
    RUN_TEST(testPrintOrder);
    RUN_TEST(testPrintBestSelling);*/
    return 0;
}
