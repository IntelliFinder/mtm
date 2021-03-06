#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"
#include "list.h"
#include "amount_set.h"
#include "matamikya_print.h"



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
/*
int main() {
    Matamikya matamikya = matamikyaCreate();
    matamikya->mtm = NULL;
    
    setAdd(Matmikya->mtm, data);
    Matamikya copy = copyMtmProductData( matamikya );
    printf("%d", compareMtmProductData(matamikya, copy) );
    freeMtmProductData( matamikya );
    freeMtmProductData( copy );

    return 0;
}
*/
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
    mpd->customData = copyData(customData);
    mpd->copyData = copyData;
    mpd->freeData = freeData;
    mpd->prodPrice = prodPrice;
    return mpd;
}
void mtmProductDestroy(MtmProduct mp){
    if (mp==NULL)
        return;
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
    MtmProduct ans = mtmProductCreate(mp->id, mp->amount,mp->name, mp->amountType, mp->amountSold, mp->customData,mp->copyData, mp->freeData,mp->prodPrice);
    return ans;
}
void itemSetFreeElement(SetElement mpV){
    if (mpV == NULL)
        return;
    MtmProduct mp = mpV;
    mp->freeData(mp->customData);
    free(mp->name);
    free(mp);
    //i think we dont need to free mp->customData because there could be one customData for many products
    //update - we do
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
    if (orderV == NULL)
        return;
    Order order = orderV;
    Set set = order->itemsSet;
    if( set != NULL ){
        setDestroy( set );
    }
    free(order);

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
    newOrder->id = maxID;
    newOrder->itemsSet = setCreate(itemSetCopyElement, itemSetFreeElement, itemSetCompareElement);
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
            setAdd(orderToChange->itemsSet, mtmProductCreate(prodInMTM->id, prodInMTM->amount,prodInMTM->name, prodInMTM->amountType,
                                              prodInMTM->amountSold, prodInMTM->customData,prodInMTM->copyData,
                                             prodInMTM->freeData,prodInMTM->prodPrice) );
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

/*============================================PRINT==================================================*/
MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if( matamikya->mtm == NULL ){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    MtmProduct maxMp = setGetFirst(matamikya->mtm);
    MtmProduct runMp = setGetFirst(matamikya->mtm);
    while (runMp != NULL){
        double incomeRun = runMp->prodPrice(runMp->customData,runMp->amountSold);
        double incomeMax = maxMp->prodPrice(maxMp->customData,maxMp->amountSold);
        if (incomeRun>incomeMax){
            maxMp = runMp;
        }
        runMp = setGetNext(matamikya->mtm);
    }
    mtmPrintIncomeLine(maxMp->name,maxMp->id,maxMp->prodPrice(maxMp->customData,maxMp->amountSold), output);
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
    if( matamikya == NULL ){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    fprintf(output, "Inventory Status:\n");
    Set iter = setCopy(matamikya->mtm); //maybe remove
    if(setGetSize(iter) == -1){
        setDestroy(iter);
        return MATAMIKYA_SUCCESS;
    }
    int size = setGetSize(iter);
    MtmProduct prod;
    for(int i=0; i<size; i++){
        if( i==0 ){
            prod = setGetFirst(iter);
            mtmPrintProductDetails(prod->name,  prod->id, prod->amount, prod->prodPrice(prod->customData, prod->amountSold), output);
        }
        else{
            prod = setGetNext(iter);
            mtmPrintProductDetails(prod->name,  prod->id, prod->amount, prod->prodPrice(prod->customData, prod->amountSold), output);
        }
    }
    setDestroy(iter); // maybe use matamikya
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output){
    if(  matamikya == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    double total=0;
    mtmPrintOrderHeading(orderId, output);
    if( findOrderWithID( matamikya->cart, orderId ) == NULL ){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    Set iter = findOrderWithID( matamikya->cart, orderId )->itemsSet;

    if(setGetSize(iter) == -1){
        return MATAMIKYA_SUCCESS;
    }
    int size = setGetSize(iter);
    MtmProduct prod;
    for(int i=0; i<size; i++){
        if( i==0 ){
            prod = setGetFirst(iter);
            total += prod->prodPrice(prod->customData,prod->amountSold);
            mtmPrintProductDetails(prod->name,  prod->id, prod->amount, prod->prodPrice(prod->customData, prod->amountSold), output);
        }
        prod = setGetNext(iter);
        mtmPrintProductDetails(prod->name,  prod->id, prod->amount, prod->prodPrice(prod->customData, prod->amountSold), output);
    }
    mtmPrintOrderSummary(total,output);
    return MATAMIKYA_SUCCESS;
}

/*===========================================END PRINT==================================================*/
