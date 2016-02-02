#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

float Get_rpi_temp() {
   int fd, size;
   char buffer[15] = { };
   fd = open("/sys/class/thermal/thermal_zone0/temp", O_RDONLY);
   size = read(fd,buffer, sizeof(buffer));
   close(fd);
   float tf = atof(buffer);
   printf("RasPi Cpu Tempture = %2.2f\n", tf/1000);
   return (tf/1000); 
}
