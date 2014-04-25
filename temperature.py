#coding=utf-8
"""获取树莓派的温度，并上传到yeelink"""
import commands
import requests
import json
from time import strftime, sleep

headers = {"U-ApiKey": "aae39f7225ba04111cc3fbc545bbc9d7"}
DEVICE_ID = "9311"
CPU_SENSOR_ID = "14695"
GPU_SENSOR_ID = "14696"


def upload_temp(sensor_type, temp):
    if sensor_type == "cpu":
        sensor_id = CPU_SENSOR_ID
        print "CPU Temp:", temp
    else:
        sensor_id = GPU_SENSOR_ID
        print "GPU Temp:", temp
    url = r"http://api.yeelink.net/v1.0/device/%s/sensor/%s/datapoints" % (DEVICE_ID, sensor_id)
    #print url
    data = {"timestamp": strftime("%Y-%m-%dT%H:%M:%S"), "value": temp}
    #print data
    r = requests.post(url, data=json.dumps(data), headers=headers)
    
def get_cpu_temp():
    tempFile = open( "/sys/class/thermal/thermal_zone0/temp" )
    cpu_temp = tempFile.read()
    tempFile.close()
    return float(cpu_temp)/1000

def get_gpu_temp():
    gpu_temp = commands.getoutput( '/opt/vc/bin/vcgencmd measure_temp' ).replace( 'temp=', '' ).replace( '\'C', '' )
    return  float(gpu_temp)

while True:
    upload_temp("cpu", get_cpu_temp())
    upload_temp("gpu", get_gpu_temp())
    sleep(20)
