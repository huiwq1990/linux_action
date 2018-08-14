
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int a=9999;

void  main(){

    int fd,data;

    char pathname[100];

    sprintf(pathname,"/proc/%d/mem",getpid());

    fd=open(pathname,O_RDONLY);

    if( fd == -1){
        printf("openerror:%m");
        exit(-1);
    }

    // read var a's val.
    pread(fd,&data,4,&a);

    //lseek(fd,&a,SEEK_SET);

    //read(fd,&data,4);

    printf("%d\n",data);

    close(fd);

}

