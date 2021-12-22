#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"
#include "matamikya_print.h"
#include "matamikya_order.h"
#include "matamikya_product.h"


/*============================================PRINT==================================================*/
void mtmPrintNone(FILE* output){
    fprintf(output,"none\r\n");
}
void mtmPrintBestSellingProd(FILE* output){
    fprintf(output,"Best Selling Product:\r\n");
}
MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output){
    if( matamikya->mtm == NULL ){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    MtmProduct maxMp = setGetFirst(matamikya->mtm);
    MtmProduct runMp = setGetFirst(matamikya->mtm);
    while (runMp != NULL){
        double incomeRun = (*runMp->prodPrice)(runMp->customData,runMp->amountSold);
        double incomeMax = (*maxMp->prodPrice)(maxMp->customData,maxMp->amountSold);
        if (incomeRun>incomeMax){
            maxMp = runMp;
        }
        runMp = setGetNext(matamikya->mtm);
    }

    mtmPrintBestSellingProd(output);

    if((*maxMp->prodPrice)(maxMp->customData,maxMp->amountSold)>0) {
        mtmPrintIncomeLine(maxMp->name,maxMp->id,(*maxMp->prodPrice)(maxMp->customData,maxMp->amountSold), output);
    }
    else{
        mtmPrintNone(output);
    }
    return MATAMIKYA_SUCCESS;
}
MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
    if( matamikya == NULL ){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    fprintf(output, "Inventory Status:\r\n");
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
            mtmPrintProductDetails(prod->name,  prod->id, prod->amount, (*prod->prodPrice)(prod->customData, 1.0), output);
        }
        else{
            prod = setGetNext(iter);
            mtmPrintProductDetails(prod->name,  prod->id, prod->amount, (*prod->prodPrice)(prod->customData, 1.0), output);
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
    mtmPrintOrderHeading(orderId, output);//change this, watch expected order
    Order midOrder = findOrderWithID( matamikya->cart, orderId );

    if( midOrder == NULL ){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    Set iter = midOrder->itemsSet;

    if(setGetSize(iter) == -1){
        return MATAMIKYA_SUCCESS;
    }
    int size = setGetSize(iter);
    MtmProduct prod;
    for(int i=0; i<size; i++){
        if( i==0 ) {
            prod = setGetFirst(iter);
        }
        else {
            prod = setGetNext(iter);
        }
        total += (*prod->prodPrice)(prod->customData,prod->amount);
        mtmPrintProductDetails(prod->name,  prod->id, prod->amount, (*prod->prodPrice)(prod->customData, prod->amount), output);
    }
    mtmPrintOrderSummary(total,output);
    return MATAMIKYA_SUCCESS;
}

/*===========================================END PRINT==================================================*/
