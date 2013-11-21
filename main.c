#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"

void main(){
	const char *host = "localhost";
  	const char *user = "userx";
  	const char *pass = "";
  	const char *db   = "nodechat";
 	/* 定义mysql变量 */
    MYSQL mysql;
    MYSQL_RES *rs;
    MYSQL_ROW row;
    /* 初始化 */
    mysql_init(&mysql); 
    
    system("mkfifo –m 666 fifo1");//create a fifo file
    
    while(1){
    
	/* 连接数据库 */
	if (!mysql_real_connect(&mysql, host, user, pass, db, 0, NULL, 0))
 	{ 
         printf("%s\n", mysql_error(&mysql));
 	}
  	char *sql = "SELECT * FROM file_table ORDER BY fid";
  	if (mysql_query(&mysql, sql)!=0) 
  	{ /* 查询 */
         printf( "%s\n", mysql_errno(&mysql), mysql_error(&mysql));
    }
   	rs = mysql_store_result(&mysql); /* 获取查询结果 */
   	
   	int num_rows = mysql_num_rows(rs);
   	if(num_rows<=0){
   		printf("Not working ...\n");
   		//no row	
   	}else{
   		while ((row = mysql_fetch_row(rs))) 
   		{   
         	printf( "fid->%s\n", row[0]);
         	printf( "path->%s\n", row[2]);
         	
         	char filebuffer[50] = "";
         	sprintf(filebuffer,"gcc -o savefile/%s %s",row[1],row[2]);
         	//printf("gcc -o %s %s",s,row[2]);
         	system(filebuffer);    //gcc compile the .c files.
         	
         	char ss[50] = "";
         	char delsql[] = "DELETE FROM file_table WHERE fid = ";
         	sprintf(ss,"%s%s",delsql,row[0]);
         	mysql_query(&mysql,ss);
         	printf("%s is delete in database.\n",row[1]);
         	
         	char s[] = "";
         	sprintf(s,"./write_fifo savefile/%s",row[1]);
         	system(s);  //write into fifo
   		}
   	}
   	mysql_free_result(rs); /* 释放结果集 */
   	mysql_close(&mysql); /* 关闭连接 */
   	
   	sleep(5);
	}
}
