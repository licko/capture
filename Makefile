all : test clean1
test : capture.o handle_ethernet.o handle_ip.o handle_tcp.o  handle_udp.o handle_data.o handle_udp_data.o search.o 
	gcc -o test capture.o handle_ethernet.o handle_ip.o handle_tcp.o   search.o handle_data.o -lpcap handle_udp.o handle_udp_data.o 
capture.o : capture.c capture.h 
	gcc -c capture.c 
handle_ethernet.o : handle_ethernet.c capture.h 
	gcc -c handle_ethernet.c 
handle_ip.o : handle_ip.c capture.h 
	gcc -c handle_ip.c 
handle_tcp.o : handle_tcp.c capture.h 
	gcc -c handle_tcp.c 
handle_udp.o : handle_udp.c capture.h 
	gcc -c handle_udp.c 
handle_data.o : handle_data.c capture.h 
	gcc -c handle_data.c 
search.o : search.c capture.h 
	gcc -c search.c 
clean1 :
	rm -rf  capture.o handle_ethernet.o handle_ip.o handle_tcp.o handle_data.o   search.o  handle_udp_data.o handle_udp.o
clean:
	rm -rf temp.txt  data.txt udpdata.txt
cleanall:
	rm -rf temp.txt  data.txt  udpdata.txt test
