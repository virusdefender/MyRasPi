// dht11_v2.go 
package main

import (
    "fmt"
    . "github.com/sndnvaps/rpi"
    "os"
)

const (
     HIGH_TIME  int = 32
     PinNumber  int = 1
)

var databuf  int
var crc      int

func ReadSensorData() int {

     var i   int
     databuf  = 1
     crc = 1 
     PinMode(PIN_GPIO_1,OUTPUT)// set pin to output 
     DigitalWrite(PIN_GPIO_1,LOW)// set to low at least 18ms
     Delay(25)
     DigitalWrite(PIN_GPIO_1, HIGH) // output a low level 
     
     //PullUpDnControl(PIN_GPIO_1,PUD_UP)
     
     DelayMicroseconds(27)
      
      PinMode(PIN_GPIO_1,INPUT) // set mode to input 
    
    // fmt.Printf("databuf == %d\n",databuf) 
     if DigitalRead(PIN_GPIO_1) == 0 { //SENSOR ANS 
              //fmt.Printf("Sensor ANS!\n")
            for DigitalRead(PIN_GPIO_1) == 0 { // wait to high 
            //fmt.Printf("Wait to high\n") 
               
               for  i = 0; i < 32; i++ {
                   for DigitalRead(PIN_GPIO_1) == 1 {/// data clock start
                           // fmt.Printf("data clock start\n")
                                 
                       for DigitalRead(PIN_GPIO_1) == 0 { //data start
                           // fmt.Printf("data start\n")
                               
                           DelayMicroseconds(HIGH_TIME)
                                   
                             //   fmt.Printf("databuf  = %d\n",databuf) 
                                  databuf = databuf * 2
                                 if DigitalRead(PIN_GPIO_1) == 1 { //1 
                                     databuf = databuf + 1
                                     }
                                 //fmt.Printf("databuf = %d\n",databuf)
                           }
                   }
               }  
               
             

          for  i = 0; i< 8; i++ {
               //fmt.Printf("Get temp ++ \n")
               for DigitalRead(PIN_GPIO_1) == 1 {
                 //   fmt.Printf("Get temp!\n")
                   for DigitalRead(PIN_GPIO_1) == 0 {
                      DelayMicroseconds(HIGH_TIME)
                      crc = crc * 2
                         if DigitalRead(PIN_GPIO_1) == 1 { // 1
                             crc++
                            // fmt.Printf("crc = %d\n",crc)
                          }
                      }
                    }
             }
          }

            return 1
          } else {
                return 0
        }

}

  

func main() {
    fmt.Printf("Use GPIO1 to read data!\n")
    err := WiringPiSetup()
    if err != nil {
        fmt.Println(err)
        os.Exit(1)
     }
     
     PinMode(PIN_GPIO_1,OUTPUT) // set mode to output 
     DigitalWrite(PIN_GPIO_1,HIGH) // output a high level 
     
     fmt.Printf("Enter OS-------\n")
    
      for ; ; {
           PinMode(PIN_GPIO_1,OUTPUT) //set mode to output 
           DigitalWrite(PIN_GPIO_1,HIGH) //output a high level 
           Delay(3000)
           if ReadSensorData() == 1 {
                fmt.Printf("Congratulations! Sensor data read ok!\n")
                fmt.Printf("RH:%d.%d\n", (databuf>>24)&0xff, (databuf>>16)&0xff)   
                fmt.Printf("TMP:%d.%d\n",(crc>>8)&0xff, crc&0xff)
                databuf = 1
                crc = 1
            } else {
                fmt.Printf("Sorry! Sensor doesn't ans!\n")
                 databuf = 1
                 crc = 1
            }
    
        } 
          os.Exit(0)
}

