#include <stdio.h>
#include <stdlib.h>

#include "matamikya.h"

struct Matamikya_t{
    int amount;
};

int main() {
    int am = 3;
    Matamikya mtm=matamikyaCreate();
    mtm->amount = am;
    printf("%d", mtm->amount);

    return 0;
}
Matamikya matamikyaCreate()
{
    Matamikya mtm = malloc(sizeof(*mtm));
    if(!mtm){
        return NULL;
    }
    return mtm;
}
