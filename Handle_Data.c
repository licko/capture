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
void Handle_Data(char *str)
{
		
		fdd = fopen("data.txt","ab");
          if(NULL == fdd)
          {
              perror("fopen fdd:");
              exit(EXIT_FAILURE);
          }
	
		int nu = Search(str);
			
		//if((nu == 1) || (ACK_old == ACK_new))
		if(nu == 1) 
		{ 	
			if (NULL != strstr(str, "Host: qurl.f.360.cn")) 
			{
				return 0;
			}
			if(data_len > 0)
			{
				
				fprintf(fd, "*****************MYWORK*****************\n");
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
	char a[5];
	strncpy(a,str,4);			
	fwrite(a,1,4,fdd);
	fwrite(str,1,data_len,fd);

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

	
	


