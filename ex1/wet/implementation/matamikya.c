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
    double amountSold;//only being used for mtm
    //,aybe compare function
    MtmProductData customData;

}*MtmProduct;

typedef struct Order_t{
    unsigned int id; //const
    Set itemsSet;
}*Order;

SetElement copyMtmProductData( SetElement set_element );
void freeMtmProductData( SetElement set_element );
int compareMtmProductData( SetElement set_element_1,SetElement set_element_2 );

void FreeListElement( SetElement setElement );
SetElement copySetElements( SetElement SetElement );
int compareSetElements( SetElement setElement, SetElement setElement );


int main() {
    Matamikya matamikya = matamikyaCreate();
    matamikya->mtm =  setCreate( copyMtmProductData, freeMtmProductData, compareMtmProductData) ;
    MtmProductData data = malloc(sizeof(*MtmProductData));
    /* *data = { 1,1, "Apple" };
    setAdd(Matmikya->mtm, data);
    Matamikya copy = copyMtmProductData( matamikya );
    printf("%d", compareMtmProductData(matamikya, copy) );
    freeMtmProductData( matamikya );
    freeMtmProductData( copy );*/
    return 0;
}

/*
MtmProduct findProductInSet(Set products, const unsigned int productId){
    if (products==NULL)
        return NULL;
    MtmProduct mpd = setGetFirst(products);
    while (mpd != NULL){
        if (productId == mpd->id)
            return mpd;
        mpd = setGetNext(products);
    }
    return NULL;
}

SetElement copyMtmProductData( SetElement set_element )
{
    if( set_element == NULL ){
        return NULL;
    }
    MtmProductData product = malloc(sizeof(*product));
    char* units = malloc(sizeof(strlen(set_element->units) + 1 ));
    product->id = set_element->id;
    product->amount = set_element->amount;
    product->units = units;
    return product;
}

void freeMtmProductData( SetElement set_element )
{
    free(set_element->units);
    free(set_element);
}
int compareMtmProductData( SetElement set_element_1, SetElement set_element_2 )
{
    if( set_element_1==NULL || set_element_2==NULL ){
        return 0; //maybe not
    }
    if( set_element_1->id > set_element_2->id ){
        return 1;
    }
    assert( set_element_1 <= set_element_2 );
    if( set_element_1->id > set_element_2  ){
        return -1;
    }
    return 0;
}

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
bool isNameValid(const char *name){
    if(name==NULL)
        return false;
    char fl=*name;//fl=first letter
    if((int)'a'<=fl && (int)'z'>=fl)
        return true;
    if ((int)'A'<=fl && (int)'Z'>=fl)
        return true;
    return (int)'0'<=fl && (int)'9'>=fl;
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
 */

/************************I start here my code****************/
/*
MtmProduct mtmProductCreate(unsigned int id, int amount,char* units, MatamikyaAmountType amountType, double discount, MtmProductData customData){
    MtmProduct mpd = malloc(sizeof(*mpd));
    mpd->amount = amount;
    mpd->id = id;
    mpd->units = units;
    mpd->amountType = amountType;
    mpd->discount = discount;
    mpd->customData = customData;
    return mpd;
}
copySetElements itemSetCopyElement(MtmProduct mp){
    MtmProduct ans = mtmProductCreate(mp->id, mp->amount, mp->units, mp->amountType, mp->discount, mp->customData);
    return ans;
}
freeSetElements itemSetFreeElement(MtmProduct mp){
    free(mp);
    //i think we dont need to free mp->customData because there could be one customData for many products
}
compareSetElements itemSetCompareElement(MtmProduct mp1,MtmProduct mp2){//compare by id
    return mp1->id - mp2->id;
}
copySetElements cartSetCopyElement(Order order){
    Order ans = malloc(sizeof(*ans));
    ans->itemsSet = itemSetCopyElement(order->itemsSet);
    ans->id = order->id;
    return ans;
}
freeSetElements cartSetFreeElement(Order order){
    itemSetFreeElement(order->itemsSet);
    free(order);
}
compareSetElements cartSetCompareElement(Order  order1,Order order2){
    return order1->id - order2->id;
}
Matamikya matamikyaCreate(){
    Matamikya ans = malloc(sizeof(*ans));
    ans->mtm = setCreate(itemSetCopyElement,itemSetFreeElement,itemSetCompareElement);
    ans->cart = setCreate(cartSetCopyElement,cartSetFreeElement,cartSetCompareElement);
    return ans;
}


*/

/*************orders**************************/
/*
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
    if (amount < 0){
        prodInOrder->amount += amount;
        if (prodInOrder->amount<=0){
            setRemove(orderToChange->itemsSet,prodInOrder);
            free(prodInOrder);
        }
        return MATAMIKYA_SUCCESS;
    }
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)//i'll do it after we will have product sales
{
    if(matamikya == NULL)
        return MATAMIKYA_NULL_ARGUMENT;
    Order shipOrder = findOrderWithID(orderId);
    if (shipOrder == NULL)
        return MATAMIKYA_ORDER_NOT_EXIST;
    MtmProduct mpSell = setGetFirst(shipOrder);
    while (mpSell != NULL){
        if
    }
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
*/
