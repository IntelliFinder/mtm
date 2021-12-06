#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <matamikya.h>
#include <set.h>

/** Type for representing a Matamikya warehouse */
typedef struct Matamikya_t{
    Set mtm;
} *Matamikya;

/** Type for additional custom data of a product */
typedef void MtmProductData_t{
    int id;
    int amount;
    char* units;

} *MtmProductData;

SetElement copyMtmProductData( SetElement set_element );
void freeMtmProductData( SetElement set_element );
int compareMtmProductData( SetElement set_element,SetElement set_element );




int main() {

    return 0;

}
SetElement copyMtmProductData( SetElement set_element )
{
    if( sel_element == NULL ){
        return NULL;
    }
    MtmProductData product = malloc(sizeof(*product));
    char* units = malloc(sizeof(strlen(set_element->units)+1));
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
    if( set_element_1->id >set_element_2  ){
        return -1;
    }
    return 0;
}
