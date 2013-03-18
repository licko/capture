/********************************************************
 * 功能：网络抓包头文件
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/

#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <net/ethernet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

extern pcap_t* descr;
 void handle_ethernet(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void handle_ip(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void handle_tcp(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void handle_udp(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void handle_data(char *str);
void handle_udp_data(char *str);

void my_callback(u_char *useless,const struct pcap_pkthdr* pkthdr,
                                             const u_char *packet);
int search(char *str);
extern unsigned long long ACK_new;
extern unsigned long long ACK_old;
extern  FILE *fd;
extern char packet_buf[1600];
extern int data_len;
extern int packet_number;

typedef struct 
{
	unsigned char smac[18];
	unsigned char dmac[18];
	unsigned char sip[16];
	unsigned char dip[16];
	unsigned long sport;
	unsigned long dport;	


}pakt;
extern pakt packet;
