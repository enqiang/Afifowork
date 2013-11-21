#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{    
    int fd[2];
    int pid;

    if (argc != 2)
    {
        printf("Usage:\n\t%s string\n", argv[0]);
        return 1;
    }

    if (pipe(fd) < 0)
    {
        printf("Unable to create pipe!\n");
        return 1;
    }

    // fork child process
    pid = fork();

    if (pid == 0) //child
    {
        close(fd[0]); //close read end
        write(fd[1], argv[1], strlen(argv[1])); //write message
        close(fd[1]); //close before exit
    }
    else if (pid > 0) //parent
    {
        char buf[1024];
        int len;

        close(fd[1]); //close write end
        len = read(fd[0], buf, sizeof(buf)); //read from the pipe
        buf[len] ='\0';
        printf("<PARENT> message from child: %s\n", buf);
        wait(NULL); //wait for child exit
        close(fd[0]); //close before exit
    }
    else
    {
        printf("Unable to fork!\n");
        return 1;
    }

    return 0;
}
