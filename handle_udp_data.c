/********************************************************
 * 功能：处理DATA函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
FILE * fdd;
char * ttt;
void insert_mysql();
int judgment(char *str);
void handle_udp_data(char *str)
{
		
		fdd = fopen("udpdata.txt","ab");
          if(NULL == fdd)
          {
              perror("fopen fdd:");
              exit(EXIT_FAILURE);
          }
	
		int nu = judgment(str);
			
		//if(nu == 1) 
		{ 	
			if(data_len > 0)
			{
				
				fprintf(fdd, "\n*****************MYWORK*****************\n");				fprintf(fdd,"The %d packet is captured.\n",packet_number);
				fprintf(fdd,"smac = %s\n",packet.smac);
				fprintf(fdd,"dmac = %s\n",packet.dmac);
				fprintf(fdd,"sip  = %s\n",packet.sip);
				fprintf(fdd,"dip  = %s\n",packet.dip);
				fprintf(fdd,"sport= %d\n",packet.sport);
				fprintf(fdd,"dport= %d\n",packet.dport);
				char *p = str;
				while(data_len--)
				{
					fprintf(fdd,"%02x ",(unsigned char) *p);
					p++;
					//fwrite(str,1,data_len,fdd);
				}
				insert_mysql();
				fprintf(fdd, "\n");
			}
		}
		fclose(fdd);
}

int judgment(char *str)
{
	char *tmp = str;
	if(32 == *tmp)
	{
			tmp = tmp + 9;
			if((*tmp == 0) && (*(tmp+1) == 0) && (*(tmp+2) == 0) 
							&& (*(tmp+3) == 0) && (*(tmp+4) == 1))
			{
				tmp = tmp + 5;
				if((*tmp == 22) && (*(tmp+1) == 3) 
					&& (*(tmp+2) == 1) && (*(tmp+5) == 1))
				return 1;
			}

		
	}


	return 0;


}
void insert_mysql()
{   
	MYSQL *conn_ptr; 
    conn_ptr = mysql_init(NULL);
 
    if (!conn_ptr)    
    {
        fprintf(stderr, "mysql_init failed\n");
        exit (0);
    }
    
    conn_ptr = mysql_real_connect(conn_ptr, "192.168.1.176", 
                        "licko", "licko", "packet", 0, NULL, 0);    
    
    if (conn_ptr)
    {
        printf("Connection success\n");
    }
    else
    {
        printf("Connection failed\n");
    }
	char *str[100];
    sprintf(str,"insert into packet values ('', '%s', '%s', '%s', '%s', %d, %d)",packet.smac, packet.dmac, packet.sip, packet.dip, packet.sport, packet.dport);
    if(mysql_query(conn_ptr, str)!=0)
	 
     {
       printf("insert data error");
         
     }
	else
     {
          printf("insert data success");
     }
   
    mysql_close(conn_ptr);
}
	
	


