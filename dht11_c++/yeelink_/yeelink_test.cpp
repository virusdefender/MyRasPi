
extern "C" {
 
#include "yeelink.h"
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
   /*
   char device_id[6];
   char sensor_id[6];
   snprintf(device_id,6, "%s","19702");
   snprintf(sensor_id,6,"%s","34550");
   */
   
    string device_ = "19702";
    string sensor_ = "34550";
    
   int val = 28;
    
    stringstream ss;
    ss << val;
    string val_s = ss.str();
    
   //printf("TT:device_id = %s\ntsensor_id = %s\nval = %d\n\n");
   cout << "device_id = " << device_ << "sensor_id = " << sensor_ << "vaL = " << val << endl;

   Yeelink_upload(device_.c_str(),sensor_.c_str(),val_s.c_str());
   return 0;
}

