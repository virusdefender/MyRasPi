
//machtalk_test.cpp 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

//for dht11

extern "C" {

#include "dht11_v2.1.h"
#include "machtalk_v1.h"

}

//void GetDht11_data(int *temp, int *rh);




using namespace std;



int main() {
   

    int temp;
    int rh;
    GetDht11_data(&temp,&rh);
    

     std::thread t1; //t1 is not a thread 
     std::thread t2(machtalk_post,"df104baddce24fd0a5e976c90fc07df3","1","1",temp,3);

     std::thread t3(machtalk_post,"df104baddce24fd0a5e976c90fc07df3","2","1",rh,3);
     t2.join();
     t3.join();

      
     
   return 0;
}

