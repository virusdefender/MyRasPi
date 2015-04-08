/* upload_dht11_data.c */
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


//for dht11 sensor 
#include <wiringPi.h>
#include <stdint.h>
#define MAX_TIME 85
#define DHT11PIN 1
#define ATTEMPTS 5                 //retry 5 times when no response
int dht11_val[5]={0,0,0,0,0};




#define PORT 80
#define REMOTE_IP "42.96.164.52" //api.yeelink.net = 42.96.164.52


#define DEVICE_ID "19702"
#define SENSOR_ID "34550" //temp
#define SENSOR_ID_2 "34551"  //RH 

#define TEMP_YEELINK 11
#define RH_YEELINK   12 

int upload_data_yeelink(int type , int val) {

     int s ;
   struct sockaddr_in addr ;
    char mybuffer[256];
        char *str1;
       printf("test type = %d\n",type);
       
       if (type == 11) {
        str1= "POST /v1.0/device/19702/sensor/34550/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n";
        } else  {
        str1="POST /v1.0/device/19702/sensor/34551/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n";
        }

	//char *str1="POST /v1.0/device/19374/sensor/33945/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n";
	char *str2="U-ApiKey: 108968b03a7e9334b2aca7c45b199dee\r\nContent-Length: 12\r\nContent-type: application/json;charset=utf-8\r\n";
	char *str3="\r\n";
        char *str10;
        printf("test value = %d\n",val);
       int t = val;
         
       sprintf(str10,"{\"value\":%d}\r\n",t);
       printf("str10 = %s\n",str10);
       
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

   bzero(&addr,sizeof(addr));
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

          
        printf("str1 = %s\n",str1);
	bzero(mybuffer,sizeof(mybuffer));

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
         bzero(mybuffer,sizeof(mybuffer));
         recv(s ,mybuffer,sizeof(mybuffer),0);
       //  printf("received:%s\n",mybuffer);
         if (strlen(mybuffer) == 0 ){    // if strlen(mybuffer) == 0, exit the loop
           return 0;
        }
    }
   
  return 1;
}

int dht11_read_val(){
    uint8_t lststate=HIGH;         //last state
    uint8_t counter=0;
    uint8_t j=0,i;
    for(i=0;i<5;i++)
        dht11_val[i]=0;
         
    //host send start signal    
    pinMode(DHT11PIN,OUTPUT);      //set pin to output 
    digitalWrite(DHT11PIN,LOW);    //set to low at least 18ms 
    delay(18);
    digitalWrite(DHT11PIN,HIGH);   //set to high 20-40us
    delayMicroseconds(40);
     
    //start recieve dht response
    pinMode(DHT11PIN,INPUT);       //set pin to input
    for(i=0;i<MAX_TIME;i++)         
    {
        counter=0;
        while(digitalRead(DHT11PIN)==lststate){     //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            counter++;
            delayMicroseconds(1);
            if(counter==255)
                break;
        }
        lststate=digitalRead(DHT11PIN);             //read current state and store as last state. 
        if(counter==255)                            //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if((i>=4)&&(i%2==0)){
            dht11_val[j/8]<<=1;                     //write 1 bit to 0 by moving left (auto add 0)
            if(counter>16)                          //long mean 1
                dht11_val[j/8]|=1;                  //write 1 bit to 1 
            j++;
        }
    }
    // verify checksum and print the verified data
    if((j>=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF))){
       // printf("RH:%d.%d\tTEMP:%d.%d\n",dht11_val[0],dht11_val[1],dht11_val[2],dht11_val[3]);
         printf("RH:%d,TEMP:%d\n",dht11_val[0],dht11_val[2]);
          int rh = dht11_val[0];
          int temp_t = dht11_val[2];
         printf("dht11 for upload_data test\n");
         printf("rh = %d\temp_t = %d\n",rh,temp_t);  
         upload_data_yeelink(12, rh);
         sleep(10);  
         upload_data_yeelink(11,temp_t);
         
        return 1;
    }
    else
        return 0;
}


int main(void){
    int attempts=ATTEMPTS;
    if(wiringPiSetup()==-1)
        exit(1);
    while(attempts){                        //you have 5 times to retry
        int success = dht11_read_val();     //get result including printing out
        if (success) {                      //if get result, quit program; if not, retry 5 times then quit
            break;
        }
        attempts--;
        delay(2500);
    }
    return 0;
}

