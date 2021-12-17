#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"
#include "list.h"
#include "amount_set.h"

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
    return 0;
}
/*=====================Matamikya===============================================*/

MtmProductData MtmCopyData( MtmProductData product )
{
    if( product == NULL ){
        return NULL;
    }
    char* name = malloc(strlen(*product->units) + 1);
    if( name ==NULL)
    {
        return NULL;
    }
    *name = *(product->units);
    MtmProductData new = { product->id, product->amount, name, product->amountType };
    return new;

}

Matamikya matamikyaCreate(){
    Matamikya ans = malloc(sizeof(*ans));
    ans->mtm = setCreate(itemSetCopyElement,itemSetFreeElement,itemSetCompareElement);
    ans->cart = setCreate(cartSetCopyElement,cartSetFreeElement,cartSetCompareElement);
    return ans;
}
void matamikyaDestroy(Matamikya matamikya){
    setDestroy(matamikya->mtm);
    setDestroy(matamikya->cart);
    free(matamikya);
}
MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id){
    if (matamikya == NULL)
        return MATAMIKYA_NULL_ARGUMENT;
    MtmProduct mpClear = findProductInSet(matamikya->mtm,id);
    if (mpClear == NULL)
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    setRemove(matamikya->mtm,mpClear);
    //remove from all orders
    Order runOrder = setGetFirst(matamikya->cart);
    while (runOrder!=NULL){
        mpClear = findProductInSet(runOrder->itemsSet,id);
        setRemove(runOrder->itemsSet,mpClear);
        runOrder = setGetNext(matamikya->cart);
    }
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{ //matamikya non-null
    if( matamikya == NULL || name==NULL || amountType ==NULL ||
        customData ==NULL || freeData ==NULL || prodPrice ==NULL )
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(!isNameValid(name)){
        return MATAMIKYA_INVALID_NAME;
    }
    assert(isNameValid(name));
    if ( amount<0 || !(amountType == MATAMIKYA_INTEGER_AMOUNT || (amountType == MATAMIKYA_ANY_AMOUNT|| (amountType == MATAMIKYA_HALF_INTEGER_AMOUNT )){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    //go over all elements in set check id take maximum and add one
    if( setIsIn(matamikya->mtm, customData) ){
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    customData->name = name;
    customData->id =id;
    customData->amount = amount;

    MtmProductData product = MtmCopyData( customData ); // why do we need more details other than customData?
    setAdd( matamilya, product );//suppose setadd already copmapares using compare function, dont see any other way
    return MATAMIKYA_SUCCESS;
}


MtmProduct mtmProductCreate(unsigned int id, int amount,char* units, MatamikyaAmountType amountType, double discount, MtmProductData customData){
    if(customData == NULL){
        return NULL;
    }
    MtmProduct mpd = malloc(sizeof(*mpd));
    mpd->amount = amount;
    mpd->id = id;
    mpd->units = units;
    mpd->amountType = amountType;
    mpd->discount = discount;
    mpd->customData = customData;
    return mpd;
}


/*===============================end matamikya===========================================*/
