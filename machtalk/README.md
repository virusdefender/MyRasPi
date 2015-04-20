

$gcc -c machtalk_v1.c
$gcc -c dht11_v2.1.c 


$ g++ -o machtalk_upload  -std=c++11 -lwiringPi  machtalk_upload.cpp machtalk_v1.o dht11_v2.1.o

$./machtalk_uplad 


