all : test clean1
test : Capture.o Handle_Ethernet.o Handle_Ip.o Handle_Tcp.o   Handle_Data.o Search.o 
	gcc -o test Capture.o Handle_Ethernet.o Handle_Ip.o Handle_Tcp.o   Search.o Handle_Data.o -lpcap 
Capture.o : Capture.c capture.h 
	gcc -c Capture.c 
Handle_Ethernet.o : Handle_Ethernet.c capture.h 
	gcc -c Handle_Ethernet.c 
Handle_Ip.o : Handle_Ip.c capture.h 
	gcc -c Handle_Ip.c 
Handle_Tcp.o : Handle_Tcp.c capture.h 
	gcc -c Handle_Tcp.c 
Handle_Data.o : Handle_Data.c capture.h 
	gcc -c Handle_Data.c 
Search.o : Search.c capture.h 
	gcc -c Search.c 
clean1 :
	rm -rf  Capture.o Handle_Ethernet.o Handle_Ip.o Handle_Tcp.o Handle_Data.o   Search.o  
clean:
	rm -rf temp.txt  data.txt 
cleanall:
	rm -rf temp.txt  data.txt  test
