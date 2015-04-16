package main
/*
#include "dht11_v2.1.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#cgo LDFLAGS:    -L. -ldht11 
#cgo CFLAGS: -I.


void my_get_dht11_data(int *tt, int *rr) {
      GetDht11_data(tt,rr);
}

void hello(const char *name) {
   printf("%s\n",name);
   return;
}


*/


import "C"

import (
      "fmt"
      "bitbucket.org/sndnvaps/callback/exp/callback"
)

/*
func GetDHT11_data(temp *int, rh *int) {
       C.GetDht11_data(C.int(temp),C.int(rh))
       fmt.Printf("temp = %d\nrh = %d\n",temp,rh)
}
*/
func Hello(s string) {
     cs := C.CString(s)
     C.hello(cs)
}

func init() {
     C.init(callback.Func)
}

func main() {
   /* 
   var t , r int
    t , r = 0, 0

    GetDHT11_data(&t,&r)
   
    fmt.Printf("tmp=%d\trh=%d\n",t,r)
    */
    Hello("Call C's go wrapper func\n")
//    C.hello(C.CString("Call c hello func"))


    return 0
}
