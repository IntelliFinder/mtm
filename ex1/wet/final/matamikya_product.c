#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "matamikya_product.h"
#include "matamikya_order.h"
#include "matamikya_print.h"

#include "set.h"

MtmProduct mtmProductCreate(unsigned int id, double amount,const char* name, MatamikyaAmountType amountType,
                            double amountSold, MtmProductData customData,MtmCopyData copyData, MtmFreeData freeData,MtmGetProductPrice prodPrice)
{
    if(customData == NULL){
        return NULL;
    }
    MtmProduct mpd = malloc(sizeof(*mpd));
    mpd->amount = amount;
    mpd->id = id;
    mpd->name = malloc((1+ strlen(name))*sizeof(char));
    strcpy((mpd->name),name);
    mpd->amountType = amountType;
    mpd->amountSold = amountSold;
    mpd->customData = (*copyData)(customData);
    mpd->copyData = copyData;
    mpd->freeData = freeData;
    mpd->prodPrice = prodPrice;
    return mpd;
}
void mtmProductDestroy(MtmProduct mp){
    if (mp==NULL){
        return;
    }
    free(mp->name);
    (*(mp->freeData))(mp->customData);
    free(mp);
}

/*=============================Set=============================================*/
MtmProduct findProductInSet(Set products, const unsigned int productId){
    if (products==NULL){
        return NULL;
    }
    MtmProduct mpd = setGetFirst(products);
    while (mpd != NULL){
        if (productId == mpd->id)
            return mpd;
        mpd = setGetNext(products);
    }
    return NULL;
}

SetElement itemSetCopyElement(SetElement mp1){
    MtmProduct mp = (MtmProduct)(mp1);
    MtmProduct ans = mtmProductCreate(mp->id, mp->amount,mp->name, mp->amountType, mp->amountSold, mp->customData,mp->copyData, mp->freeData,mp->prodPrice);
    return ans;
}
void itemSetFreeElement(SetElement mpV){
    if (mpV == NULL){
        return;
    }
    MtmProduct mp = mpV;
    mtmProductDestroy(mp);
    /*
    mp->freeData(mp->customData);
    free(mp->name);
    free(mp);*/
    //i think we dont need to free mp->customData because there could be one customData for many products
    //update - we do
}
int itemSetCompareElement(SetElement mp11,SetElement mp21){//compare by id
    MtmProduct mp1 = mp11;
    MtmProduct mp2 = mp21;
    return ((int)(mp1->id) - (int)(mp2->id));
}

bool isNameValid(const char *name){
    if(name==NULL){
        return false;
    }
    char fl=*name;//fl=first letter
    if((int)'a'<=fl && (int)'z'>=fl){
        return true;

    }
    if ((int)'A'<=fl && (int)'Z'>=fl){
        return true;
    }
    return ((int)'0'<=fl && (int)'9'>=fl);
}
bool isAmountValid(const MtmProduct mp,const double wantedAmount){
    double diff = (double)wantedAmount - (int)wantedAmount;
    if( mp->amountType == MATAMIKYA_INTEGER_AMOUNT ){
        if( diff <= 0.001 || diff >= 0.999){
            return true;
        } else{
            return false;
        }
    }
    if( mp->amountType == MATAMIKYA_HALF_INTEGER_AMOUNT ){
        if( diff <= 0.001 || diff >= 0.999){
            return true;
        }
        if( (diff-0.5) <= 0.001 && (diff-0.5)>=-0.001){
            return true;
        }
        return false;
    }
    assert(mp->amountType==MATAMIKYA_ANY_AMOUNT);
    return true;

}

/**==============================end set and help functions=========================================**/


/**=====================Matamikya===============================================**/

Matamikya matamikyaCreate(){
    Matamikya ans = malloc(sizeof(*ans));
    ans->mtm = setCreate(itemSetCopyElement,itemSetFreeElement,itemSetCompareElement);
    ans->cart = setCreate(cartSetCopyElement,cartSetFreeElement,cartSetCompareElement);
    if ( ans->mtm == NULL || ans->cart == NULL ){
        return NULL;
    }
    return ans;
}
void matamikyaDestroy(Matamikya matamikya){
    setDestroy(matamikya->mtm);
    setDestroy(matamikya->cart);
    free(matamikya);
}
MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id){
    if (matamikya == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    MtmProduct mpClear = findProductInSet(matamikya->mtm,id);
    if (mpClear == NULL){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    setRemove(matamikya->mtm, mpClear);
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
{
    if( matamikya == NULL || name == NULL || customData == NULL || copyData == NULL || freeData == NULL || prodPrice ==NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(!isNameValid(name)){
        return MATAMIKYA_INVALID_NAME;
    }
    assert(isNameValid(name));
    MtmProduct product = mtmProductCreate(id, amount,name, amountType,0, customData,copyData, freeData,prodPrice);
    if ( amount<0 || !isAmountValid(product,amount)){
        mtmProductDestroy(product);
        return MATAMIKYA_INVALID_AMOUNT;
    }

    if( setIsIn(matamikya->mtm, product) ) {
        mtmProductDestroy(product);
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    setAdd( matamikya->mtm, product );
    return MATAMIKYA_SUCCESS;
}


/*===============================end matamikya===========================================*/

