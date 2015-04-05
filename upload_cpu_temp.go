package main

import (
   "fmt"
   "io/ioutil"
   "net"
   "time"
   "os"
)


func checkError(err error) {
     if err != nil {
        fmt.Fprintf(os.Stderr, "Fatal error: %s\n",err.Error())
        os.Exit(1)

        }
}



func main() {
        //Connet the api.yeelink.net 
        //REMOTE_IP 42.96.164.52 
        //PORT      80 
        
        conn, err := net.Dial("tcp","42.96.164.52:80")
        defer conn.Close()
        checkError(err)
        fmt.Printf("Post Request \n")
        time.Sleep(time.Second)
 
    _  , err = conn.Write([]byte("POST /v1.0/device/19374/sensor/33945/datapoints HTTP/1.0\r\nHost: api.yeelink.net\r\nAccept: */*\r\n")) 


    if err != nil {
           fmt.Printf("Sent Requset ok\n")
        }
/*
    checkError(err)
    result, err := ioutil.ReadAll(conn)//get the info 
    checkError(err)
  
  fmt.Println(string(result))
*/
        fmt.Printf("Send the API-keys\n")
        time.Sleep(time.Second)

    // send the API-key 
     _ , err = conn.Write([]byte("U-ApiKey: 108968b03a7e9334b2aca7c45b199dee\r\nContent-Length: 15\r\nContent-type: application/json;charset=utf-8\r\n"))
         checkError(err)
        time.Sleep(time.Second)
     //send the '\r\n'
     _ , err = conn.Write([]byte("\r\n"))
       checkError(err)

      //send the value 
      time.Sleep(time.Second)
      var value string 
           
      value = fmt.Sprintf("{\"value\":19.12}\n\n")
      
      
     //_ , err = conn.Write([]byte("{\"value\":13.14}\r\n"))
     // var b []byte

      //b = str2byte(value)
     // fmt.Println("b = ", b) 

       _, err = conn.Write([]byte(value))
         
         checkError(err)
        time.Sleep(time.Second)
      result, err := ioutil.ReadAll(conn)
      checkError(err)
      fmt.Println(string(result))
       
    os.Exit(1)
}


