//
// Created by vagrant on 8/19/18.
//
//https://blog.csdn.net/ordeder/article/details/21716639

#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int nr;
    char buff[20];
    printf("parent pid:%d\n",getpid());

    int fd1 = open("data.in",O_RDWR);
    pid_t pid = fork();


    if(pid == 0)
    {
        nr = read(fd1,buff,10);
        buff[nr]='\0';
        printf("pid#%d content#%s#\n",getpid(),buff);
        exit(0);
    }
    nr = read(fd1,buff,10);
    buff[nr]='\0';
    printf("pid#%d content#%s#\n",getpid(),buff);
    return 0;
}