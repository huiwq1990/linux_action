#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>  
int main()
{
    pid_t pid;
    int fd = open("test.txt", O_RDWR | O_APPEND | O_CREAT,S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd == -1)
    {
        perror("errno");
        printf("open file error.\n");
        return 1;
    }
    /* reset file content */
    ftruncate(fd,0);
    lseek(fd,0,SEEK_SET);

    printf("open file's fd = %d\n", fd);
    // set close on exec
    fcntl(fd, F_SETFD, 1);
    char *s = "ooooooooooooooooooo";
    pid = fork();
    if (pid == 0)
    {
        printf("child thread exec.");
        execl("ass", "./ass", &fd, NULL);
    }
    wait(NULL);
    write(fd, s, strlen(s));
    close(fd);
    return 0;
}