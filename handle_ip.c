/********************************************************
 * 功能：解析IP层数据
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"

void handle_ip(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        struct ip * ip_protocol;
        u_int header_length;                            /*首部长度*/
        u_int offset;                                   /*偏移*/
        u_char tos;                                     /*服务质量*/
        u_int16_t checksum;                             /*校验和*/
		u_int total;
        
        //获得IP协议数据内容,应该跳过以太网协议头
        ip_protocol = (struct ip *)(packet_content+14);
	char *sip = inet_ntoa(ip_protocol->ip_src); 
	if(0 !=strcmp(sip,"192.168.1.166"))
	{
		return 0;
	}

	fprintf(fd,"----------------------- IP Protocol (Network Layer) ---------------\n");
        checksum = ntohs(ip_protocol->ip_sum);
        header_length = ip_protocol->ip_hl * 4;
        tos = ip_protocol->ip_tos;
        offset = ntohs(ip_protocol->ip_off);
		total = ntohs(ip_protocol->ip_len);
		data_len = total - header_length;
	fprintf(fd,"The %d packet is captured.\n",packet_number);
        fprintf(fd,"IP Version:%d\n",ip_protocol->ip_v);
        fprintf(fd,"Header length:%d\n",header_length);
        fprintf(fd,"TOS:%d\n",tos);
        fprintf(fd,"Total length:%d\n",total);
        fprintf(fd,"Identification:%d\n",ntohs(ip_protocol->ip_id));
        fprintf(fd,"Offset:%d\n",(offset & 0x1fff)*8);
        fprintf(fd,"TTL:%d\n",ip_protocol->ip_ttl);
        fprintf(fd,"Protocol:%d\n",ip_protocol->ip_p);

	
        /*switch(ip_protocol->ip_p)
        {
                case 6:fprintf(fd,"The Transport Layer Protocol is TCP\n");
			printf("The Transport Layer Protocol is TCP\n");break;
                case 17:fprintf(fd,"The Transport Layer Protocol is UDP\n");
			printf("The Transport Layer Protocol is UDP\n");break;
                case 1:fprintf(fd,"The Transport Layer Protocol is ICMP\n");break;
                default:printf("The Transport Layer Protocol is ***\n");break;
        }*/
	if(ip_protocol->ip_p == 17)
	{	printf("The Transport Layer Protocol is UDP\n");
	}
	else
	{	printf("The Transport Layer Protocol is ***\n");
	}
		fprintf(fd,"Header checksum:%d\n",checksum);

	
	
       // fprintf(fd,"Source address     :%s\n",inet_ntoa(ip_protocol->ip_src));
	fprintf(fd,"Source address     :%s\n",sip);
		strcpy(packet.sip,sip);
		//fprintf(fd,"Destination address:%s\n",inet_ntoa(ip_protocol->ip_dst));
		char *dip = inet_ntoa(ip_protocol->ip_dst);
		fprintf(fd,"Destination address:%s\n",dip);
		strcpy(packet.dip,dip);
        switch(ip_protocol->ip_p)
        {
               	case 6:handle_tcp(argument,packet_header,packet_content);break;
                case 17:handle_udp(argument,packet_header,packet_content);break;
                default:break;
        }
}
