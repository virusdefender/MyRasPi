/*client.c*/
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
#define PORT 80
#define REMOTE_IP "42.96.164.52" //api.yeelink.net = 42.96.164.52

//#define PORT 4321
//#define REMOTE_IP "192.168.1.104"


 int GetCpuTemp() {
//char *GetCpuTemp() {

    int fd, size;
    int temp = 0;
   char buffer[15] = { };
   fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
   size = read(fd,buffer, sizeof(buffer));
   close(fd);
    int tmp;
  // strcpy(tmp,buffer);

   temp = atoi(buffer);
  // printf("temp = %d\n",temp / 1000);

  // sprintf(tmp,"%d",temp / 1000);
  // printf(" temp1 =%s\n",tmp);
  // printf(" temp2 = %s\n",buffer);

   return (temp/1000) ;
}



int   main(int argc,char *argv[])
{   
   int s ;
   struct sockaddr_in addr ;
    char mybuffer[256];
	char *str1="POST /v1.0/device/19374/sensor/33945/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n";
	char *str2="U-ApiKey: 108968b03a7e9334b2aca7c45b199dee\r\nContent-Length: 12\r\nContent-type: application/json;charset=utf-8\r\n";
	char *str3="\r\n";
        char *str10;
        printf("GetCpuTemp() = %d\n",GetCpuTemp());
      
       sprintf(str10,"{\"value\":%d}\r\n",GetCpuTemp());
    //   printf("str10 = %s\n", str10);
   //    char *str10="{\"value\":14}\r\n";
   //  printf("str10 = %s\n",str10);
       
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
    return 0;
}


