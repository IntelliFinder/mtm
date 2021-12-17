#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"
#include "list.h"
#include "amount_set.h"
#include "matamikya_set.c"
#include "matamikya_matamikya.c"
#include "matamikya_order.c"

/** Type for representing a Matamikya warehouse */
struct Matamikya_t{
    Set mtm;
    Set cart;
};

/** Type for additional custom data of a product */
typedef struct MtmProduct_t{
    unsigned int id; //const
    double amount;
    char* units;
    MatamikyaAmountType amountType;
    double discount; //percent*(1/100)
    double amountSold;//only being used for mtm, remember that when created needs to be 0
    //maybe compare function
    MtmProductData customData;
    MtmCopyData copyData;
    MtmFreeData freeData;
    MtmGetProductPrice prodPrice;

}*MtmProduct;

typedef struct Order_t{
    unsigned int id; //const
    Set itemsSet;
}*Order;

int main() {
    Matamikya matamikya = matamikyaCreate();
    matamikya->mtm =    NULL;
    /*
    setAdd(Matmikya->mtm, data);
    Matamikya copy = copyMtmProductData( matamikya );
    printf("%d", compareMtmProductData(matamikya, copy) );
    freeMtmProductData( matamikya );
    freeMtmProductData( copy );
     */
    return 0;
}