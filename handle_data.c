/********************************************************
 * 功能：处理DATA函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
#include <mysql/mysql.h>
FILE * fdd;
char * ttt;
char hostt[100];
void host(char *str);
void referer(char *str);
void post(char *str);
void insert_mysql();
void handle_data(char *str)
{
		fdd = fopen("data.txt","ab");
	memset(hostt, 0, 100);
          if(NULL == fdd)
          {
              perror("fopen fdd:");
              exit(EXIT_FAILURE);
          }
	
		int nu = search(str);
			
		//if((nu == 1) || (ACK_old == ACK_new))
		if(nu == 1) 
		{ 	
			if((NULL != strstr(str, "Host: qurl.f.360.cn")) || (NULL != strstr(str, "q.soft.360.cn")) || (NULL != strstr(str, "Host: softm.update.360safe.com")) || (NULL != strstr(str, "Host: safe.track.uc.360.cn")) || (NULL != strstr(str, "Host: up.f.360.cn")) || (NULL != strstr(str, "Host: fodder.qq.com")) || (NULL != strstr(str, "s1.bdstatic.com")) || (NULL != strstr(str, "ynote.youdao")) )
			{
				return 0;
			}
			if(data_len > 0)
			{
				
				
				fprintf(fdd,"smac = %s\n",packet.smac);
				fprintf(fdd,"dmac = %s\n",packet.dmac);
				fprintf(fdd,"sip  = %s\n",packet.sip);
				fprintf(fdd,"dip  = %s\n",packet.dip);
				fprintf(fdd,"sport= %d\n",packet.sport);
				fprintf(fdd,"dport= %d\n",packet.dport);
				fwrite(str,1,data_len,fd);
				fflush(fd);
				if(strstr(str,"Host"))
				{	
					host(str);				
				}															
				if(strstr(str,"Referer"))
				{	
					
					referer(str);					
				}
			
			}
				insert_mysql();
				ACK_old = ACK_new;
		}
		fclose(fdd);
}
void post(char *str)
{
	fprintf(fdd, "\n*****************MYWORK*****************\n");	
	char a[4];
	char *tmp = strstr(str,"POST");
	int i;	
	for(i=0; i<4; i++ )
	{
		fwrite(tmp,1,1,fdd);
		tmp++;	
	}	

	fprintf(fdd, "\n");	
		
}

void host(char *str)
{
		
	char *p = str;
	char *q;	
	//Host
	q = strstr(p, "Host");	
	
	p = NULL;
	p = strstr(q, "\r\n"); 
	if(p != NULL) 
	{			
		*p = '\0';	              	      		
		//strcpy(hostt,q);
		sprintf(hostt, "%s", q);	
		int len_11 = strlen(q); 
		fwrite(q,1,len_11,fdd);
		fprintf(fdd, "\n");
	}
	
}
void referer(char *str)
{
	
	char *p = str;
	char *q;	
	q = strstr(p, "Referer");
	p = NULL;
	p = strstr(q, "\r\n") ;
	if(p != NULL)
	{	
		*p = '\0';	
		int len_11 = strlen(q); 
		printf(" ===%d", len_11);
		fwrite(q,1,len_11,fdd);
	}
	
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
    sprintf(str,"insert into packet values ('', '%s', '%s', '%s', '%s', %d, %d, '%s')",packet.smac, packet.dmac, packet.sip, packet.dip, packet.sport, packet.dport, hostt);
   printf("*&&&&&&&&&&&&&&&&&%s\n",hostt);
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

	
	


