#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;
    unsigned char *buff;
    buff = (char *) malloc(sizeof(char)*1024);
    printf("my pid is:%d\n",getpid());
    sleep(3600);
    /* code */
    return 0;
}
