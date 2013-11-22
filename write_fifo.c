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
	int rtn;   //子进程返回值
	int n, i ;
	char buf[BUFES];
	time_t tp;
	printf("I am %d\n",getpid()); /*说明进程的ID*/
	if((fd=open("fifo1",O_WRONLY))<0){ /*以写打开一个FIFO1*/
		perror("open");
		exit(1);
	}
	
	if ( fork() == 0 ) {/* 子进程执行此命令 */
        execlp( argv[1], NULL );   /* 如果exec函数返回，表明没有正常执行命令，打印错误信息*/
        perror( argv[1] );
        exit( errno );
    }
    else {/* 父进程， 等待子进程结束，并打印子进程的返回值 */
        wait ( &rtn );
        n=sprintf(buf," %d return value is %d\n",getpid(),rtn);
		printf("Send msg:%s\n",buf);
        if((write(fd, buf, n))<0) { 
			perror("write");
			close(fd); 
			exit(1);
		}
        //printf( " child process return %s\n", rtn );
    }

	sleep(3); /*进程睡眠3秒*/
	close(fd); /* 关闭FIFO文件 */
	exit(0);
}
