/********************************************************
 * 功能：解析数据链路层数据
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
void Handle_Ethernet(u_char *argument,const struct pcap_pkthdr * packet_header,const u_char * packet_content)
{
        u_short ethernet_type;
        struct ether_header * ethernet_protocol;
        u_char * mac_string;
        static int packet_number = 1;
        printf("***********************************************\n");
        printf("The %d TCP packet is captured.\n",packet_number);
        printf("----- Ethernet Protocol (Link Layer) --------\n");
        ethernet_protocol = (struct ether_header *)packet_content;
        printf("Ethernet type is : ");
        ethernet_type = ntohs(ethernet_protocol->ether_type);
        printf("%04x\n",ethernet_type);
        switch(ethernet_type)
        {
                case 0x0800:printf("The network layer is IP protocol\n");break;
                case 0x0806:printf("The network layer is ARP protocol\n");break;
                case 0x0835:printf("The network layer is RARP protocol\n");break;
                default:break;
        }
        printf("Mac Source Address is:");
        mac_string=ethernet_protocol->ether_shost;
        printf("%02x:%02x%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
        printf("Mac Destination Address is:");
        mac_string=ethernet_protocol->ether_dhost;
        printf("%02x:%02x%02x:%02x:%02x:%02x\n",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));

        switch(ethernet_type)
        {
                case 0x0800:Handle_Ip(argument,packet_header,packet_content);
                break;
                default:break;
        }
        printf("********************************\n");
        packet_number++;
}
