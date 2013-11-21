#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#define BUFES PIPE_BUF

int main(int argc,char *argv[]){
	int fd ;
	int n, i ;
	char buf[BUFES];
	time_t tp;
	printf("I am %d\n",getpid()); /*说明进程的ID*/
	if((fd=open("fifo1",O_WRONLY))<0){ /*以写打开一个FIFO1*/
		perror("open");
		exit(1);
	}
	
	n=sprintf(buf," %d sends %s",getpid(),argv[1]);
	printf("Send msg:%s\n",buf);
	if((write(fd, buf, n+1))<0) { /*写入到FIFO中*/
		perror("write");
		close(fd); /* 关闭FIFO文件 */
		exit(1);
	}
	sleep(3); /*进程睡眠3秒*/
	
	close(fd); /* 关闭FIFO文件 */
	exit(0);
}
