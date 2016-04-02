MyRasPi
=======

我的树莓派，最近会逐渐写一点运行在上面的python脚本。
 http://www.machtalk.net/device/dataview/df104baddce24fd0a5e976c90fc07df3 可以在这里看到结果。

Add C language && golang support 

Add DHT11 sensor support 
Add DHT22 sensor support 

Add machtalk.net support 

add std::thread support (need c++11 support )

add mysql support (dht22)


# upload dht22 && rpi_cpu_temp to machtalk per minute 

	1. Copy cronfile to /home/pi/ folder 
	2. Setup crontab 
			$ crontab  /home/pi/cronfile 
	3. Replace [machtalk/dht22/machtalk_dht22.cpp] line 69 && line 70 with you own info 
	4. Build for you pi 
			$ git clone https://github.com/sndnvaps/MyRasPi.git 
			$ cd MyRasPi 
			$ sudo su
			$ cd machtalk
			$ vim dht22/dht22.h # setup dht22 for you own gpio pin , i was set to gpio pin 7 
			$ cmake . 
			$ make install 
	5. have fun ,you have success install machtalk_dht22 into you pi /usr/local/bin/ 


#TODO 

[] Add [iniparser](https://github.com/ndevilla/iniparser) support 



