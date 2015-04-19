
extern "C" {
 
#include "machtalk.h"
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <sstream>

using namespace std;



int main() {
   
    string device_ = "df104baddce24fd0a5e976c90fc07df3";
    
   double val = 28;
    
    stringstream ss;
    ss << val;
    string val_s = ss.str();
    
   cout << "device_id = " << device_ <<  "vaL = " << val << endl;

   machtalk_upload(device_.c_str(),val_s.c_str());
   return 0;
}

