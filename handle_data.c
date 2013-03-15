/********************************************************
 * 功能：处理DATA函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
FILE * fdd;
char * ttt;
void host(char *str);
void referer(char *str);
void handle_data(char *str)
{
		
		fdd = fopen("data.txt","ab");
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
				
				fprintf(fd, "*****************MYWORK*****************\n");
				fwrite(str,1,data_len,fd);
				host(str);							
					
				if(strstr(str,"Referer"))
				{	
					referer(str);					
				}
			}
				ACK_old = ACK_new;
		}
		fclose(fdd);
}
void host(char *str)
{
	fprintf(fdd, "\n*****************MYWORK*****************\n");	
	fprintf(stdout, "\n*****************ERROR*****************\n");	
	char a[4];
	char *tmp = strstr(str,"POST");
	//fprintf(stdout, "\ntmp = %s\n",tmp);	
	fprintf(stdout, "\n*****************ERROR1*****************\n");
	int i;	
	for(i=0; i<4; i++ )
	{
		fwrite(tmp,1,1,fdd);
		tmp++;	
	}	
	fprintf(stdout, "\n*****************ERROR2*****************\n");		
	
	fprintf(stdout, "\n*****************ERROR3*****************\n");
	fprintf(fdd, "\n");	
		


	char *p = str;
	char *q;	
	//Host
	q = strstr(p, "Host");	
	p = strstr(q, "\r");
	*p = '\0';	              	      		
	
	int len_11 = strlen(q); 
	fwrite(q,1,len_11,fdd);
	fprintf(fdd, "\n");

}

void referer(char *str)
{
	
	char *p = str;
	char *q;	
	q = strstr(p, "Referer");
	p = strstr(q, "\r");
	*p = '\0';	
	int len_11 = strlen(q); 
	fwrite(q,1,len_11,fdd);
}	

	
	


