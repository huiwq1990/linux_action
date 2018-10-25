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

int main(int argc, char *argv[])
{
    int fd;
    //printf("argc = %d\n", argc);
    fd = *argv[1];
    printf("child rec fd = %d\n", fd);
    char *s = "zzzzzzzzzzzzzzzzzzz";
    write(fd, (void *)s, strlen(s));
    close(fd);
    return 0;
}