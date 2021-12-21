#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "set.h"
#include "matamikya.h"
typedef struct Order_t{
    unsigned int id; //const
    Set itemsSet;
}*Order;

unsigned int mtmCreateNewOrder(Matamikya matamikya);

Order findOrderWithID(const Set cart,const unsigned int orderId);

SetElement cartSetCopyElement(SetElement orderV);

void cartSetFreeElement(SetElement orderV);

int cartSetCompareElement(SetElement order11,SetElement order21);
