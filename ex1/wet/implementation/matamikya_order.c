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
        return MATAMIKYA_NULL_ARGUMENT;
    Order orderToChange = findOrderWithID(matamikya->cart,orderId);

    if (orderToChange==NULL)
        return MATAMIKYA_ORDER_NOT_EXIST;
    MtmProduct prodInMTM = findProductInSet(matamikya->mtm,productId);
    MtmProduct prodInOrder = findProductInSet(orderToChange->itemsSet,productId);
    if (prodInMTM == NULL) {


        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if (amount==0.0)
        return MATAMIKYA_SUCCESS;
    if (prodInOrder==NULL){
        if(amount<0)
            return MATAMIKYA_INVALID_AMOUNT;
        if (amount>0){
            setAdd(orderToChange->itemsSet, mtmProductCreate(productId, amount, prodInMTM->units, prodInMTM->amountType,prodInMTM->discount,prodInMTM->customData));
            return MATAMIKYA_SUCCESS;
        }
    }
    assert(prodInOrder);
    if (amount>0){
        prodInOrder->amount = prodInOrder->amount + amount;
        return MATAMIKYA_SUCCESS;
    }
    else{
        assert(amount<0);
        prodInOrder->amount += amount;
        if (prodInOrder->amount<=0){
            setRemove(orderToChange->itemsSet,prodInOrder);
            free(prodInOrder);
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
    //set.h says that free func is being used
    return MATAMIKYA_SUCCESS;
}

/**=============================end orders=============================**/