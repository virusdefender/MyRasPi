
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
//for std::mutex 
#include <mutex>
//for dht11

extern "C" {

#include "dht11_v2.1.h"
#include "machtalk_v1.h"

}


using namespace std;

//void GetDht11_data(int *temp, int *rh);

std::mutex g_mutex;

void Machtalk_Post(string device_id, string device_value_id, string device_value_type_id, float value, int overtime) {
     g_mutex.lock();
     machtalk_post(device_id.c_str(),device_value_id.c_str(),device_value_type_id.c_str(),value,overtime);
     g_mutex.unlock();

}   


using namespace std;



int main() {
   

    int temp;
    int rh;
    GetDht11_data(&temp,&rh);
    

     std::thread t1; //t1 is not a thread 
     std::thread t2(Machtalk_Post,"df104baddce24fd0a5e976c90fc07df3","1","1",temp,3);
   //  sleep(10);
     std::thread t3(Machtalk_Post,"df104baddce24fd0a5e976c90fc07df3","2","1",rh,3);
    
     //t4 && t5 for test 
  //   std::thread t4(Machtalk_Post,"df104baddce24fd0a5e976c90fc07df3","2","1",60.25,3);
  //   std::thread t5(Machtalk_Post,"df104baddce24fd0a5e976c90fc07df3","1","1",12.33,3);

     t2.join();
     t3.join();
   //t4.join();
   //t5.join();
     
   return 0;
}

