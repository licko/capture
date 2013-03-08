/********************************************************
 * 功能：网络抓包工具
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
// pcap_t *descr;
// const u_char *packets;
// struct pcap_pkthdr hdr;     /* pcap.h                    */
// struct ether_header *eptr;
 unsigned long long ACK_new = 0;
 unsigned long long ACK_old = 0;
 FILE *fd;
 int data_len ;
// char packet_buf[1600];
void main()
{
		fd = fopen("temp.txt","ab");
		if(NULL == fd)
		{
	    	perror("fopen fd:");
	    	exit(EXIT_FAILURE);
		}
	
	        pcap_t * pcap_handle;
        char error_content[PCAP_ERRBUF_SIZE];
        char * net_interface;
        struct bpf_program bpf_filter;
        char bpf_filter_string[] = "ip";
        bpf_u_int32 net_mask;
        bpf_u_int32 net_ip;
        net_interface = pcap_lookupdev(error_content);
        pcap_lookupnet(net_interface,&net_ip,&net_mask,error_content);
        pcap_handle = pcap_open_live(net_interface,BUFSIZ,1,0,error_content);
        pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,0,net_ip);
        pcap_setfilter(pcap_handle,&bpf_filter);
        if(pcap_datalink(pcap_handle)!=DLT_EN10MB)
                return;
        pcap_loop(pcap_handle,-1,Handle_Ethernet,NULL);
        pcap_close(pcap_handle);
		fclose(fd);

}
