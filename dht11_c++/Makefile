dht11_v2.1:dht11_v2.1.o
	gcc -shared -o libdht11.so -lwiringPi dht11_v2.1.o
dht11_v2.1.o: dht11_v2.1.c 
	gcc -c dht11_v2.1.c -lwiringPi

dht11_v2.1_link: dht11_v2.1_link.o
	gcc -o dht11_v2.1_link -lwiringPi dht11_v2.1_link.o ./libdht11.so
dht11_v2.1_link.o:dht11_v2.1_link.c
	gcc -c dht11_v2.1_link.c -lwiringPi ./libdht11.so

PHONY: clean
clean: 
	rm *.so *.o 
	rm dht11_v2.1_link 
