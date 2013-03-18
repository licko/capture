/********************************************************
 * 功能：处理TCP数据函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/

#include "capture.h"
void handle_udp(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        struct udphdr *udp_protocol;
		u_int16_t sport;       /* source port */  
		u_int16_t dport;       /* destination port */
		u_int16_t ulen;        /* udp length */   
		u_int16_t sum;  		  /* udp checksum */
        //获得UDP协议数据内容,应该跳过以太网头和IP头部分
        udp_protocol = (struct udphdr*)(packet_content+14+20);
        sport = ntohs(udp_protocol->source);
        dport = ntohs(udp_protocol->dest);
		ulen = ntohs(udp_protocol->len);
		sum = ntohs(udp_protocol->check);

		fprintf(fd,"------------------UDP Protocol(Transport Layer)------------------\n");
		fprintf(fd,"Source Port:%d\n",sport);
		fprintf(fd,"Destination Port:%d\n",dport);
		packet.sport = sport;
		packet.dport = dport;
		fprintf(fd,"udp length:%u\n",ulen);
		fprintf(fd,"udp checksum:%d\n",sum);
		fprintf(fd,"\n");
		data_len -= 8; 
		handle_udp_data(packet_content+14+20+8);
}
