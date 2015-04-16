package main

import (
         "fmt"
      .  "github.com/sndnvaps/rpi"
         "os"
 )

 const (
      MAX_TIME int = int(37)
          ATTEMPS int  = int(5)
          DHT11_PIN  int = int(1) //PIN_GPIO_1
          //BoardToPin(12)
 )

 var dht11_val[5] int

 func dht11_read_val() int {
     var lststate int
     var counter int
     var j     int

          lststate = HIGH
          counter  = 0
          j        = 0
          var i int
          for i = 0; i < 5; i++ {
               dht11_val[i] = 0
          }

          PinMode(PIN_GPIO_1,OUTPUT) //set pin to output
          DigitalWrite(PIN_GPIO_1,LOW) //set to low at least 18ms
          Delay(18)
          DigitalWrite(PIN_GPIO_1,HIGH)  //set to high 20-40us
          DelayMicroseconds(40)

          //start receive dht response

          PinMode(PIN_GPIO_1,INPUT)
          for i = 0; i < 32; i++  {
             counter = 0

           for  DigitalRead(PIN_GPIO_1) == lststate   {   //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
                   counter++
                //   fmt.Printf("Counter = %d\n",counter)
                   DelayMicroseconds(1)
                   if counter == 255 {
                           break
                           }

                           lststate = DigitalRead(PIN_GPIO_1) //read current state and store as last

                      // fmt.Printf("lststate = %d\n",lststate)
                       
                      if  counter==255 {                          //if dht always high for 255 + 1 times, break this for circle
                         break
                                   }
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
         for  i>=4 && i%2==0 {
           //fmt.Printf("j = %d\n",j)
          if j > 38  {
             break
            }
          // fmt.Printf("dht11_val[%d] = %d\n",j/8,dht11_val[j/8] )

            dht11_val[j/8] = dht11_val[j/8] << 1                  //write 1 bit to 0 by moving left (auto add 0)
            if counter > 16 {                    //long mean 1
            //    fmt.Printf("counter > 16 :: counter == %d\n",counter)
                
                dht11_val[j/8] = dht11_val[j/8] |1                //write 1 bit to 1
              //  fmt.Printf(" counter :: dht11_val[%d] = %d\n", j/8 , dht11_val[j/8])



            }
                j++

        }
    }
                // verify checksum and print the verified data
    if j>39 && dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF){
        fmt.Printf("RH:%d,TEMP:%d\n",dht11_val[0],dht11_val[2])
        return 1
       }
     }

return 0


}


func main() {
       attemptes := ATTEMPS
       var success int
       success = 0

        err :=  WiringPiSetup()
        if err != nil {
        fmt.Println(err)
        os.Exit(1)
        }

        for  attemptes > 0 {
         success = dht11_read_val()
         if success == 1  {
         break
         }

         attemptes--
         Delay(2500)
        }
       os.Exit(0)
 //return 0

}
