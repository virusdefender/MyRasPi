#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

//for dht11 

extern "C" {

#include "dht11_v2.1.h"
}


/*
 void GetDht11_data(int *temp, int *rh);
*/ 


 
void f1(int n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread " << n << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 

void DisplayTemp_RH(int t, int r) {
        for (int i = 0; i < 5; i++ ) {
           std::cout << "Temp = " << t << std::endl;
           std::cout << "RH = " << r << std::endl;
           std::this_thread::sleep_for(std::chrono::milliseconds(10));
          }
}



void f2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        std::cout << "Thread 2 executing\n";
        ++n;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
 
int main()
{
    int n = 0;
    int tt = 0;
    int rr = 0;
    GetDht11_data(&tt,&rr);
    
    std::thread t1; // t1 is not a thread
    std::thread t2(f1, n + 1); // pass by value
    
    std::thread t3(f2, std::ref(n)); // pass by reference
    
    
    std::thread t4(std::move(t3)); // t4 is now running f2(). t3 is no longer a thread
    
    std::thread t5(DisplayTemp_RH,tt,rr);
      
   
    t2.join();
    t4.join();
    t5.join();
    std::cout << "Final value of n is " << n << '\n';
}


