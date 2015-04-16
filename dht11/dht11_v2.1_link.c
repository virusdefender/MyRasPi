#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "dht11_v2.1.h"

int main() {
    int r, t;
    r = 0;
    t = 0;
    GetDht11_data(&t,&r);
    printf("temp =%d\trh = %d\n",t,r);
    return 0;
}


