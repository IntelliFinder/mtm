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
    char* name;

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
    matamikya->mtm = NULL;
    /*
    setAdd(Matmikya->mtm, data);
    Matamikya copy = copyMtmProductData( matamikya );
    printf("%d", compareMtmProductData(matamikya, copy) );
    freeMtmProductData( matamikya );
    freeMtmProductData( copy );
     */
    return 0;
}

MtmProduct mtmProductCreate(unsigned int id, double amount,char* name, MatamikyaAmountType amountType,
                            double discount, double amountSold, MtmProductData customData,MtmCopyData copyData, MtmFreeData freeData,MtmGetProductPrice prodPrice)
{
    if(customData == NULL){
        return NULL;
    }
    MtmProduct mpd = malloc(sizeof(*mpd));
    mpd->amount = amount;
    mpd->id = id;
    mpd->name = malloc(sizeof( strlen(name) + 1 ));
    strcpy((mpd->name),name);
    mpd->amountType = amountType;
    mpd->discount = discount;
    mpd->amountSold = amountSold;
    mpd->customData = copyData(customData);
    mpd->copyData = copyData;
    mpd->freeData = freeData;
    mpd->prodPrice = prodPrice;
    return mpd;
}
void mtmProductDestroy(MtmProduct mp){
    free(mp->name);
    mp->freeData(mp->customData);
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
    MtmProduct ans = mtmProductCreate(mp->id, mp->amount,mp->name, mp->amountType, mp->discount, mp->amountSold, mp->customData,mp->copyData, mp->freeData,mp->prodPrice);
    return ans;
}
void itemSetFreeElement(SetElement mpV){
    MtmProduct mp = mpV;
    mp->freeData(mp->customData);
    free(mp);
    //i think we dont need to free mp->customData because there could be one customData for many products
}
int itemSetCompareElement(SetElement mp11,SetElement mp21){//compare by id
    MtmProduct mp1 = mp11;
    MtmProduct mp2 = mp21;
    return ((int)(mp1->id) - (int)(mp2->id));
}
SetElement cartSetCopyElement(SetElement orderV){
    Order ans = malloc(sizeof(*ans));
    Order order = orderV;
    ans->itemsSet = itemSetCopyElement((Order)(order)->itemsSet);
    ans->id = order->id;
    return ans;
}
void cartSetFreeElement(SetElement orderV){
    Order order = orderV;
    itemSetFreeElement(order->itemsSet);
    free(orderV);
}
int cartSetCompareElement(SetElement order11,SetElement order21){
    Order order1 = order11;
    Order order2 = order21;
    return (int)order1->id - (int)order2->id;
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

/**==============================end set=========================================**/


/*=====================Matamikya===============================================*/

MtmProductData MtmProductCopyData( MtmProductData product )
{
    if( product == NULL ){
        return NULL;
    }
    MtmProduct new = *(MtmProduct*)product;
    return new;

}

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
    if( matamikya == NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(!isNameValid(name)){
        return MATAMIKYA_INVALID_NAME;
    }
    assert(isNameValid(name));
    if ( amount<0){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    MtmProduct product = mtmProductCreate(id, amount,name, amountType,                                    
                                          discount, amountSold, customData,copyData, freeData,prodPrice); //go over all elements in set check id take maximum and add one
    if( setIsIn(matamikya->mtm, product) ){
        mtmProductDestroy( product );
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    
    setAdd( matamikya->mtm, product );
    return MATAMIKYA_SUCCESS;
}


/*===============================end matamikya===========================================*/

/*************orders**************************/

unsigned int mtmCreateNewOrder(Matamikya matamikya){
    unsigned int maxID = 0;
    Order runOrder = setGetFirst(matamikya->cart);
    while (runOrder!=NULL){
        if(maxID<runOrder->id){
            maxID=runOrder->id;
        }
        runOrder = setGetNext(matamikya->cart);
    }
    maxID++;
    Order newOrder = malloc(sizeof(*newOrder));
    newOrder->id=maxID;
    newOrder->itemsSet= setCreate(itemSetCopyElement, itemSetFreeElement, itemSetCompareElement);
    setAdd(matamikya->cart,newOrder);
    return maxID;//id will start with 1 and not a 0
}
Order findOrderWithID(const Set cart,const unsigned int orderId){
    Order runOrder = setGetFirst(cart);
    while (runOrder != NULL){
        if (runOrder->id == orderId)
            return runOrder;
        runOrder = setGetNext(cart);
    }
    return NULL;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                              const unsigned int productId, const double amount){
    if (matamikya==NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Order orderToChange = findOrderWithID(matamikya->cart,orderId);

    if (orderToChange==NULL)
    {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    MtmProduct prodInMTM = findProductInSet(matamikya->mtm,productId);
    MtmProduct prodInOrder = findProductInSet(orderToChange->itemsSet,productId);
    if (prodInMTM == NULL) {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if (amount==0.0){
        return MATAMIKYA_SUCCESS;
    }
    if (prodInOrder==NULL){
        if(amount<0)
            return MATAMIKYA_INVALID_AMOUNT;
        if (amount>0){
            setAdd(orderToChange->itemsSet, mtmProductCreate(prodInMTM->id, prodInMTM->amount,prodInMTM->name, prodInMTM->amountType,
                                             prodInMTM->discount, prodInMTM->amountSold, prodInMTM->customData,prodInMTM->copyData,
                                             prodInMTM->freeData,prodInMTM->prodPrice) );
            return MATAMIKYA_SUCCESS;
        }
    }
    assert(prodInOrder);
    if (amount>0){
        prodInOrder->amount = prodInOrder->amount + amount;
        if( (double)prodInOrder->amount - (int) ){

        }
        return MATAMIKYA_SUCCESS;
    }
    else{
        assert(amount<0);
        prodInOrder->amount += amount;
        if (prodInOrder->amount<=0){
            setRemove(orderToChange->itemsSet,prodInOrder);
            //free(prodInOrder); //unnecessary already done by set
        }
        return MATAMIKYA_SUCCESS;
    }
    return MATAMIKYA_SUCCESS;
}


MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(matamikya == NULL)
        return MATAMIKYA_NULL_ARGUMENT;
    Order shipOrder = findOrderWithID(matamikya->cart,orderId);
    if (shipOrder == NULL)
        return MATAMIKYA_ORDER_NOT_EXIST;
    MtmProduct mpOrderSell = setGetFirst(shipOrder->itemsSet);
    //check there is enough amount in warehouse
    MtmProduct mpMtmSell;
    while (mpOrderSell != NULL){
        mpMtmSell = findProductInSet(matamikya->mtm,mpOrderSell->id);
        if (mpOrderSell->amount > mpMtmSell->amount)
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        mpOrderSell = setGetNext(shipOrder->itemsSet);
    }
    //now we can actually ship
    mpOrderSell = setGetFirst(shipOrder->itemsSet);
    while (mpOrderSell != NULL){
        mpMtmSell = findProductInSet(matamikya->mtm,mpOrderSell->id);
        mpMtmSell->amountSold += mpOrderSell->amount;//assumes amount is good and not 0.0011
        mpMtmSell->amount -= mpOrderSell->amount;

        mpOrderSell = setGetNext(shipOrder->itemsSet);
    }
    mtmCancelOrder(matamikya,orderId);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId){
    if (matamikya == NULL)
        return MATAMIKYA_NULL_ARGUMENT;
    Order  toCancel = findOrderWithID(matamikya->cart,orderId);
    if (toCancel == NULL)
        return MATAMIKYA_ORDER_NOT_EXIST;
    setRemove(matamikya->cart,toCancel);
    //free function used as in initialization
    return MATAMIKYA_SUCCESS;
}


MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
    
}
/**=============================end orders=============================**/
