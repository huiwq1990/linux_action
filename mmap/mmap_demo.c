#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include<unistd.h>
#include <errno.h>

#define BUF_SIZE 100

//http://soledede.iteye.com/blog/2072596

int touchFile(char* fileName){

    // O_CREAT 若欲打开的文件不存在则自动建立该文件。
    // O_TRUNC 若文件存在并且以可写的方式打开时，此旗标会令文件长度清为0，而原来存于该文件的资料也会消失。
    int fd=open(fileName,O_RDWR|O_TRUNC|O_CREAT,0777);
    if(fd==-1)
    {
        printf("open error is %s\n",strerror(errno));
    }
    else
    {
        //打印文件描述符号
        printf("success fd = %d\n",fd);
        char buf[100];
        memset(buf,0,sizeof(buf));
        strcpy(buf,"hello world\n");
        write(fd,buf,strlen(buf));
        close(fd);
    }
    return 0;

}

int main(int argc, char *argv[]){
    int fd, nread, i;
    struct stat sb;
    char *mapped, buf[BUF_SIZE];

    char * fileName = "/tmp/mmaptest2";

    touchFile(fileName);

    for (i = 0; i < BUF_SIZE; i++) {
        buf[i] = '#';
    }

    /* 打开文件 */
    if ((fd = open(fileName, O_RDWR)) < 0) {
        perror("open");
    }

    /* 获取文件的属性 */
    if ((fstat(fd, &sb)) == -1) {
        perror("fstat");
    }

    /* 将文件映射至进程的地址空间 */
    if ((mapped = (char *)mmap(NULL, sb.st_size, PROT_READ |
                                                 PROT_WRITE, MAP_SHARED, fd, 0)) == (void *)-1) {
        perror("mmap");
    }

    /* 映射完后, 关闭文件也可以操纵内存 */
    close(fd);

    printf("%s", mapped);

    /* 修改一个字符,同步到磁盘文件 */
    mapped[0] = '9';
    if ((msync((void *)mapped, sb.st_size, MS_SYNC)) == -1) {
        perror("msync");
    }

    /* 释放存储映射区 */
    if ((munmap((void *)mapped, sb.st_size)) == -1) {
        perror("munmap");
    }

    return 0;
}
