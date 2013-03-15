/********************************************************
 * 功能：处理DATA函数
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
FILE * fdd;
char * ttt;
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
			
		if(nu == 1) 
		{ 	
			if(data_len > 0)
			{
				
				fprintf(fdd, "\n*****************MYWORK*****************\n");				fprintf(fdd,"The %d packet is captured.\n",packet_number);
				char *p = str;
				while(data_len--)
				{
					fprintf(fdd,"%02x ",(unsigned char) *p);
					p++;
					//fwrite(str,1,data_len,fdd);
				}
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
		if((*tmp == 0) && (*(tmp+1) == 0) && (*(tmp+2) == 0) && (*(tmp+3) == 0) && (*(tmp+4) == 1))
		{
			tmp = tmp + 5;
			if((*tmp == 22) && (*(tmp+1) == 3) && (*(tmp+2) == 1) && (*(tmp+5) == 1))
			return 1;
		}

	}


	return 0;


}
	
	

