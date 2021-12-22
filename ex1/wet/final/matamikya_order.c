#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "matamikya_print.h"
#include "matamikya_order.h"
#include "matamikya_product.h"

#include "set.h"

/*************orders**************************/
SetElement cartSetCopyElement(SetElement orderV){
    Order ans = malloc(sizeof(*ans));
    if(ans==NULL){
        return NULL;
    }
    Order order = orderV;
    //ans->itemsSet = itemSetCopyElement(order->itemsSet);
    /**====fix bug here**/
    ans->itemsSet = setCopy(order->itemsSet);
    ans->id = order->id;
    return ans;
}
void cartSetFreeElement(SetElement orderV){
    if (orderV == NULL)
    {
        return;
    }
    Order order = orderV;
    //Set set = order->itemsSet; directly to set lets see if it matters
    if( set != NULL ){
        setDestroy( order->itemsSet );
    }
    free(order);

}
int cartSetCompareElement(SetElement order11,SetElement order21){
    Order order1 = order11;
    Order order2 = order21;
    return (int)order1->id - (int)order2->id;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya){
    unsigned int maxID = 0;
    Order runOrder = setGetFirst(matamikya->cart);
    while (runOrder!=NULL){
        if(maxID<runOrder->id){
            maxID=runOrder->id;
        }
        runOrder = setGetNext(matamikya->cart);
    }
    assert(runOrder==NULL);
    maxID++;
    Order newOrder = malloc(sizeof(*newOrder));
    newOrder->id = maxID;
    newOrder->itemsSet = setCreate(itemSetCopyElement, itemSetFreeElement, itemSetCompareElement);
    assert(newOrder->itemsSet != NULL);
    setAdd(matamikya->cart,newOrder);
    return maxID;//id will start with 1 and not a 0
}
Order findOrderWithID(const Set cart,const unsigned int orderId){
    if(cart == NULL){
        return NULL;
    }
    Order runOrder = setGetFirst(cart);
    while (runOrder != NULL){
        if (runOrder->id == orderId)
            return runOrder;
        runOrder = setGetNext(cart);
    }
    return NULL;
}
MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount){
    if (matamikya==NULL)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    MtmProduct prodInMTM = findProductInSet(matamikya->mtm,id);
    if (prodInMTM == NULL) {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if (amount==0.0){
        return MATAMIKYA_SUCCESS;
    }
    if (amount>0){
        if(isAmountValid(prodInMTM, prodInMTM->amount + amount) ){
            prodInMTM->amount = prodInMTM->amount + amount;
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_INVALID_AMOUNT;
    }
    else{
        assert(amount<0);
        if (prodInMTM->amount + amount < 0){
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
        assert(prodInMTM->amount + amount >= 0);
        if(isAmountValid(prodInMTM, (prodInMTM->amount) + amount) ) {
            prodInMTM->amount += amount;
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_INVALID_AMOUNT;
    }
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
            return MATAMIKYA_INVALID_AMOUNT;//there is no instruction what to do here-- snir: i think we should remove thi, later in ship order if there is a problem we throw an error
        if (amount>0){
            if (!isAmountValid(prodInMTM,amount)){
                return MATAMIKYA_INVALID_AMOUNT;
            }
            MtmProduct mpAdd= mtmProductCreate(prodInMTM->id, amount,prodInMTM->name, prodInMTM->amountType,
                                               prodInMTM->amountSold, prodInMTM->customData,prodInMTM->copyData,
                                               prodInMTM->freeData,prodInMTM->prodPrice);
            assert(mpAdd);
            setAdd(orderToChange->itemsSet, mpAdd);
            return MATAMIKYA_SUCCESS;
        }
    }
    assert(prodInOrder);
    if (amount>0){
        if(isAmountValid(prodInOrder, prodInOrder->amount+amount) ){
            //if(prodInMTM->amount >= prodInOrder->amount + amount) { dont need to check it, read MATAMIKYA.h
            prodInOrder->amount = prodInOrder->amount + amount;
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_INVALID_AMOUNT;
    }
    else{
        assert(amount<0);
        if (prodInOrder->amount + amount<=0){
            setRemove(orderToChange->itemsSet,prodInOrder);
            return MATAMIKYA_SUCCESS;
        }
        if(isAmountValid(prodInOrder, prodInOrder->amount+amount) ) {
            prodInOrder->amount += amount;
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_INVALID_AMOUNT;
    }
}


MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(matamikya == NULL){
        return MATAMIKYA_NULL_ARGUMENT;

    }
    Order shipOrder = findOrderWithID(matamikya->cart,orderId);
    if (shipOrder == NULL){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    MtmProduct mpOrderSell = setGetFirst(shipOrder->itemsSet);
    //check there is enough amount in warehouse
    MtmProduct mpMtmSell=NULL;
    while (mpOrderSell != NULL){
        mpMtmSell = findProductInSet(matamikya->mtm,mpOrderSell->id);
        if (mpOrderSell->amount > mpMtmSell->amount){
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
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



/**=============================end orders=============================**/
