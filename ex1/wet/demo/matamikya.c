#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matamikya.h"
#include "set.h"
#include "list.h"
#include "amount_set.h"


typedef void Order_t{
    unsigned int id;
    Set order;
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
    if( !(65<=(int)(*name) <=90 || 97<=(int)(*name)<=122 || 0<=(int)(*name)<=9)){
        return MATAMIKYA_INVALID_NAME;
    }
    assert( (65<=(int)(*name) <=90 || 97<=(int)(*name)<=122 || 0<=(int)(*name)<=9) );
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
