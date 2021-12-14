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
typedef struct MtmProductData_t{
    unsigned int id;
    int amount;
    char* units;
    MatamikyaAmountType amountType;
    double discount; //percent*(1/100)
    //,aybe compare function

}*MtmProductData;

typedef struct Order_t{
    unsigned int id;
    Set itemsSet;
}*Order;

SetElement copyMtmProductData( SetElement set_element );
void freeMtmProductData( SetElement set_element );
int compareMtmProductData( SetElement set_element_1,SetElement set_element_2 );

void FreeListElement( SetElement setElement );
SetElement copySetElements( SetElement SetElement );
int compareSetElements( SetElement setElement, SetElement setElement );


int main() {
    Matamikya matamikya = { setCreate( copyMtmProductData, freeMtmProductData\
                                                    , compareMtmProductData) };
    MtmProductData data = { 1,1, "Apple" };
    setAdd(Matmikya->mtm, data);                                                    
    Matamikya copy = copyMtmProductData( matamikya );
    printf("%d", compareMtmProductData(matamikya, copy) );
    freeMtmProductData( matamikya );
    freeMtmProductData( copy );
    return 0;
}


MtmProductData findProductInSet(Set products, const unsigned int productId){
    if (products==NULL)
        return NULL;
    MtmProductData mpd = setGetFirst(products);
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
    char* units = malloc(sizeof(strlen( set_element->units) + 1 ));
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
    newOrder->itemsSet= setCreate();
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
MtmProductData mtmProductDataCreate(unsigned int id, int amount,char* units, MatamikyaAmountType amountType, double discount){
    MtmProductData mpd = malloc(sizeof(*mpd));
    mpd->amount = amount;
    mpd->id = id;
    mpd->units = units;
    mpd->amountType = amountType;
    mpd->discount = discount;
    return mpd;
}
MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                              const unsigned int productId, const double amount){
    if (Matamikya==NULL)
        return MATAMIKYA_NULL_ARGUMENT;
    Order orderToChange = findOrderWithID(matamikya->cart);
    orderToChange=5;
    if (orderToChange==NULL)
        return MATAMIKYA_ORDER_NOT_EXIST;
    MtmProductData prodInMTM = findProductInSet(matamikya->mtm,productId);
    MtmProductData prodInOrder = findProductInSet(orderToChange->itemsSet,productId);
    if (prodInMTM == NULL) {


        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if (amount==0.0)
        return MATAMIKYA_SUCCESS;
    if (prodInOrder==NULL){
        if(amount<0)
            return MATAMIKYA_INVALID_AMOUNT;
        if (amount>0){
            setAdd(orderToChange->itemsSet, mtmProductDataCreate(productId, amount, prodInMTM->units, prodInMTM->amountType,prodInMTM->discount));
            return MATAMIKYA_SUCCESS;
        }
    }
    assert(prodInOrder);
    if (amount>0){
        prodInOrder->amount = prodInOrder->amount + amount;
        return MATAMIKYA_SUCCESS
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
