/* 
* yeelink.c
*/

//void Yeelink_upload(const char *device_name, const char *sensor_id, const char* val);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <memory.h>

//for yeelink.h 
#include "yeelink.h"


#define PORT 80
#define REMOTE_IP "42.96.164.52" //api.yeelink.net = 42.96.164.52


#define DEVICE_ID "19702"
#define SENSOR_ID "34550" //temp
#define SENSOR_ID_2 "34551"  //RH 

#define TEMP_YEELINK 11
#define RH_YEELINK   12 

//val = 28, 17, 29 .........
/*
* device_name = "19702" 
* sensor_id = "34550" || "34551"
*/

void Yeelink_upload(const char* device_name, const char* sensor_id,const char* val) {


    int s;
    struct sockaddr_in addr ;
    char mybuffer[256] = {'\0'} ;
    char str1[256];
    char str10[12];

      printf("Test: device_name = %s\tsensor_id = %s\tval = %s\t\n",device_name,sensor_id,val);
    
    //sprintf(str1,"POST /v1.0/device/%s/sensor/%s/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n",device_name,sensor_id);
    
	strcat(str1,"POST /v1.0/device/");
        printf("T1: str1 = %s\n", str1);
    
        strcat(str1,device_name);
        strcat(str1,"/sensor/");
        strcat(str1,sensor_id);
        strcat(str1,"/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n");
 
        printf("str1 = %s\n",str1);
        
        char *str2="U-ApiKey: 108968b03a7e9334b2aca7c45b199dee\r\nContent-Length: 12\r\nContent-type: application/json;charset=utf-8\r\n";
	char *str3="\r\n";
        //char *str10;
      //  printf("test value = %d\n",val);
      // int t = val;
    //    printf("str2 = %s\n",str2);
       //char val_t[3];
       //itoa(val,val_t,10);
       strcat(str10,"{\"value\":");
       strcat(str10,val);
       strcat(str10,"}\r\n");

       //sprintf(str10,"{\"value\":%d}\r\n",t);
      printf("str10 = %s\n",str10);
//       printf("str1 = %s\n", str1);
     
   if( (s=socket(AF_INET,SOCK_STREAM,0))<0 )  //IPV4 TCP
   {
      perror("socket");
      exit(1);
   }
   else
   {
    	printf("socket created .\n");
    	printf("socked id: %d \n",s);
	}

    //bzero(&addr,sizeof(addr));
    memset(&addr, 0, sizeof(addr));
    
   addr.sin_family =AF_INET;  //IPV4
   addr.sin_port=htons(PORT); //SERVER PORT
   addr.sin_addr.s_addr=inet_addr(REMOTE_IP);  //SERVER IP

   if(connect(s,(struct sockaddr *)&addr,sizeof(addr))<0)
   {
      perror("connect");
      exit(1);
   }
   else
   {
   	   printf("connected ok!\n");
   	   printf("remote ip:%s\n",REMOTE_IP);
   	   printf("remote port:%d\n",PORT);
    }
        printf("test for tcp send\n");
          
        // printf("str1 = %s\n",str1);
        //printf("str1 = %s\n",str1);
	//bzero(mybuffer,sizeof(mybuffer));
        //bzero(mybuffer,256);
        //memset(mybuffer, 0, 256*sizeof(char));
        printf("after memset()");
        
          
//send http request
	printf("tcp send start!--");
         
   if(send(s,str1,strlen(str1),0)<0)
      {
         perror("send");
         exit(1);
      }
   if(send(s,str2,strlen(str2),0)<0)
      {
         perror("send");
         exit(1);
      }
   if(send(s,str3,strlen(str3),0)<0)
      {
         perror("send");
         exit(1);
      }
//body
   if(send(s,str10,strlen(str10),0)<0)
      {
         perror("send");
         exit(1);
      }

   printf("tcp send ok!--");

   recv(s ,mybuffer,sizeof(mybuffer),0);
   printf("%s\n",mybuffer);
   printf("enter os");
   
   while(1 )
   {
         // bzero(mybuffer,sizeof(mybuffer));
         memset(mybuffer, 0, 256*sizeof(char));
         
         recv(s ,mybuffer,sizeof(mybuffer),0);
       //  printf("received:%s\n",mybuffer);
         if (strlen(mybuffer) == 0 ){    // if strlen(mybuffer) == 0, exit the loop
          exit(0);
        }
    }
   
  exit(0);
}


