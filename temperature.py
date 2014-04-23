#coding=utf-8
"""获取树莓派的CPU和GPU温度，并上传到yeelink"""
import commands
import requests
import json
from time import strftime

headers = {"U-ApiKey": "aae39f7225ba04*******c545bbc9d7"}
DEVICE_ID = "9311"
CPU_SENSOR_ID = "14695"
GPU_SENSOR_ID = "14696"


def upload_temp(sensor_type, temp):
    if sensor_type == "cpu":
        sensor_id = CPU_SENSOR_ID
    else:
        sensor_id = GPU_SENSOR_ID
    url = r"http://api.yeelink.net/v1.0/device/%s/sensor/%s/datapoints" % (DEVICE_ID, sensor_id)
    data = {"timestamp": strftime("%Y-%m-%dT%H:%M:%S"), "value": temp}
    r = requests.post(url, data=json.dumps(data), headers=headers)
    print r.content
    
def get_cpu_temp():
    tempFile = open( "/sys/class/thermal/thermal_zone0/temp" )
    cpu_temp = tempFile.read()
    tempFile.close()
    return float(cpu_temp)/1000

def get_gpu_temp():
    gpu_temp = commands.getoutput( "/opt/vc/bin/vcgencmd measure_temp" ).replace( "temp=", "" ).replace( "'C", "" )
    return  float(gpu_temp)

upload_temp("cpu", get_cpu_temp())
upload(temp("gpu", get_gpu_temp())
