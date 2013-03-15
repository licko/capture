/********************************************************
 * 功能：处理TCP数据函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/

#include "capture.h"
void handle_tcp(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        struct tcphdr *tcp_protocol;
        u_char flags;                           /*标志*/
        int header_length;                      /*首部长度*/
        u_short source_port;                    /*源端口号*/
        u_short destination_port;               /*目的端口号*/
        u_short windows;                        /*窗口大小*/
        u_short urgent_pointer;                 /*紧急指针*/
        u_int sequence;                         /*序列号*/
        u_int acknowledgement;                  /*确认号*/
        u_int16_t checksum;                     /*校验和*/
        //获得TCP协议数据内容,应该跳过以太网头和IP头部分
        tcp_protocol = (struct tcphdr*)(packet_content+14+20);
        source_port = ntohs(tcp_protocol->source);
        destination_port = ntohs(tcp_protocol->dest);
        header_length = tcp_protocol->doff * 4;
        sequence = ntohl(tcp_protocol->seq);
        acknowledgement = ntohl(tcp_protocol->ack_seq);
		ACK_new = acknowledgement;
        windows = ntohs(tcp_protocol->window);
        urgent_pointer = ntohs(tcp_protocol->urg_ptr);
       // flags = tcp_protocol->tcp_protocol->tcp_protocol->tcp_protocol->tcp_protocol->tcp_protocol->tcp_protocol->;
        checksum = ntohs(tcp_protocol->check);
		data_len = data_len - header_length;

       fprintf(fd,"------------------TCP Protocol(Transport Layer)------------------\n");
       fprintf(fd,"Source Port:%d\n",source_port);
       fprintf(fd,"Destination Port:%d\n",destination_port);
		fprintf(fd,"Sequence Number:%u\n",sequence);
		fprintf(fd,"Acknowledgement Number:%u\n",acknowledgement);
		fprintf(fd,"Header Length:%d\n",header_length);
		fprintf(fd,"Reserved:%d\n",tcp_protocol->res1);
		//fprintf(fd,"Flags:");
		
		//if(flags & 0x08)   printf("PSH ");
		//if(flags & 0x10)   printf("ACK ");
		//if(flags & 0x02)   printf("SYN ");
		//if(flags & 0x20)   printf("URG ");
		//if(flags & 0x01)   printf("FIN ");
		//if(flags & 0x04)   printf("RST ");
		fprintf(fd,"\n");
		fprintf(fd,"Window Size:%d\n",windows);
		fprintf(fd,"Checksum:%x\n",checksum);
		fprintf(fd,"Urgent pointer:%d\n",urgent_pointer);
		switch(destination_port)        //判断上层协议类型
		        {
                case 80:fprintf(fd,"HTTP Protocol\n");
						handle_data(packet_content+14+20+header_length);break;
                case 21:fprintf(fd,"FTP Protocol\n");break;
                case 23:fprintf(fd,"TELNET Protocol\n");break;
                case 25:fprintf(fd,"SMTP Protocol\n");break;
                case 110:fprintf(fd,"POP3 Protocol\n");break;
                default:break;
        }
}
