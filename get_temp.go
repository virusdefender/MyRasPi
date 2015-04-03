package main

import (
	"encoding/json"
	"fmt"
	"os"
	"strconv"
	//"net/http"
	//"net/url"
	//"io/ioutil"
	//"encoding/json"
	"time"
)

/*
const (
	header = {"U-ApiKey:","108968b03a7e9334b2aca7c45b199dee"}
	DEVICE_ID = "19374"
	CPU_SENSOR_ID = "33945"
	url = " http://api.yeelink.net/v1.0/device/19374/sensor/33945/datapoints"

)
*/
func GetCpuTemp() (t string) {
	tf, err := os.Open("/sys/class/thermal/thermal_zone0/temp")
	if err != nil {
		fmt.Printf("read cpu file error= %s\n", err)

	}
	defer tf.Close()
	data := make([]byte, 5)
	tf.Read(data)

	data_temp := string(data)

	temp, _ := strconv.Atoi(data_temp)
	cpu_temp := int(temp / 1000)
	t = fmt.Sprintf("%d", cpu_temp)

	return t
}

/*
func upload(data string) {

	  client := &http.Client{}
	  //time_ := time.Now()
	  //cpu_t := GetCpuTemp()
	 time_t string
	 cpu_t string
	json.NewEncoder()
	fmt.sprintf(time_t,"%s",time.Now())
	fmt.Sprintf(cpu_t,"%d",GetCpuTemp())
	data := {"timestamp":time_,"values":cpu_t}
	 json.Marshal(data)
	 ioutil.NopCloser()
	 resp , err := http.NewRequest("POST",string(url),)


}
*/

func main() {

	type YeelinkJsonData struct {
		Timestamp string
		Value     string
	}

	t := time.Now()
	//tt := t.Format("2006-01-02T15:04:05")
	//cpu_temp := GetCpuTemp()

	//js_o := YeelinkJsonData{tt, cpu_temp}

	yeelinkdata := YeelinkJsonData{
		//t.Format("2006-01-02T15:04:05"),
		//GetCpuTemp(),
		Timestamp: t.Format("2006-01-02T15:04:05"),
		Value:     GetCpuTemp(),
	}

	//js_o := '{"timestame":tt,"value":"cpu_temp"}'
	//var dat map[string]interface{}

	//fmt.Printf("js_o = %v\n", js_o)

	js, e := json.Marshal(yeelinkdata)
	if e != nil {
		fmt.Printf("Marshal failed")
		return
	}

	fmt.Println(js)
	os.Stdout.Write(js)

	var js_re YeelinkJsonData
	json.Unmarshal(js, &js_re)

	fmt.Println(js_re)

	//fmt.Printf("time : %s\nCpu Temp : %s \n", tt, cpu_temp)
	/*
		type ColorGroup struct {
			ID     int
			Name   string
			Colors []string
		}
		group := ColorGroup{
			ID:     1,
			Name:   "Reds",
			Colors: []string{"Crimson", "Red", "Ruby", "Maroon"},
		}
		b, err := json.Marshal(group)
		if err != nil {
			fmt.Println("error:", err)
		}
		os.Stdout.Write(b)
	*/
}
