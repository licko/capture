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
#include <net/ethernet.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

extern pcap_t* descr;
 void Handle_Ethernet(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void Handle_Ip(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void Handle_Tcp(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content);
void Handle_Data(char *str);
void My_CallBack(u_char *useless,const struct pcap_pkthdr* pkthdr,
                                             const u_char *packet);
int Search(char *str);
extern unsigned long long ACK_new;
extern unsigned long long ACK_old;
extern  FILE *fd;
extern char packet_buf[1600];
extern int data_len;
