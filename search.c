/********************************************************
 * 功能：应用层数据过滤
 * 环境: GCC-4.1.2
 * 作者：licko
 * 备注：自由软件，主要用于学习、交流、共享。
 *******************************************************/
#include "capture.h"
int search(char *str)
{	
	char *tmp = str;
		char *p = NULL ;
        char *q = NULL ;
	char *o;
       // p = strstr(tmp, "post");
        q = strstr(tmp, "GET");
 
        if(NULL != q)
         {
			return 1;
         }
		
		else
			return 0;
}
