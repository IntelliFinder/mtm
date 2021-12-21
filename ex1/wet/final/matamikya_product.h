#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"


/** Type for additional custom data of a product */
typedef struct MtmProduct_t{
    unsigned int id; //const
    double amount;
    char* name;
    MatamikyaAmountType amountType;
    double amountSold;//only being used for mtm, remember that when created needs to be 0
    //maybe compare function
    MtmProductData customData;
    MtmCopyData copyData;
    MtmFreeData freeData;
    MtmGetProductPrice prodPrice;
}*MtmProduct;


MtmProduct mtmProductCreate(unsigned int id, double amount,const char* name, MatamikyaAmountType amountType,
                            double amountSold, MtmProductData customData,MtmCopyData copyData, MtmFreeData freeData,MtmGetProductPrice prodPrice);

void mtmProductDestroy(MtmProduct mp);

MtmProduct findProductInSet(Set products, const unsigned int productId);

SetElement itemSetCopyElement(SetElement mp1);

void itemSetFreeElement(SetElement mpV);

int itemSetCompareElement(SetElement mp11,SetElement mp21);

bool isNameValid(const char *name);

bool isAmountValid(const MtmProduct mp,const double wantedAmount);

