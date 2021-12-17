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
SetElement itemSetCopyElement(SetElement mp1){
    MtmProduct mp = (MtmProduct)(mp1);
    MtmProduct ans = mtmProductCreate(mp->id, mp->amount, mp->units, mp->amountType, mp->discount, mp->customData);
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


/**==============================end set=========================================**/

