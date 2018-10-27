

#include <sys/socket.h>
 
#include <sys/types.h>
 
#include <sys/epoll.h>
 
#include <netinet/in.h>
 
#include <arpa/inet.h>
 
#include <fcntl.h>
 
#include <unistd.h>
 
#include <stdio.h>
 
#include <stdlib.h>
 
#include <string.h>
 
#include <pthread.h>
 
#include <errno.h>
 
#define MAXLINE 100
 
#define OPEN_MAX 100
 
#define LISTENQ 20
 
#define SERV_PORT 8888
 
#define INFTIM 1000
 
//用于读写两个的两个方面传递参数
 
struct user_data
 
{
 
int fd;
 
unsigned int n_size;
 
char line[MAXLINE];
 
};
 
//声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
 
struct epoll_event ev, events[20];
 
int epfd;
 
pthread_mutex_t mutex;
 
pthread_cond_t cond1;
 
struct task *readhead = NULL, *readtail = NULL, *writehead = NULL;
 
int i, 
 
maxi, 
 
listenfd, 
 
connfd, 
 
sockfd, 
 
nfds;
 
unsigned int n;
 
struct user_data *data = NULL;
 
struct user_data *rdata = NULL;//用于读写两个的两个方面传递参数
 
socklen_t clilen;
 
struct sockaddr_in clientaddr;
 
struct sockaddr_in serveraddr;
 
void setnonblocking(int sock)
 
{
 
int opts;
 
opts = fcntl(sock, F_GETFL);
 
if (opts < 0)
{
perror("fcntl(sock,GETFL)");
exit(1);
}
opts = opts | O_NONBLOCK;
if (fcntl(sock, F_SETFL, opts) < 0)
{
perror("fcntl(sock,SETFL,opts)");
exit(1);
}
}
void init()
{
listenfd = socket(AF_INET, SOCK_STREAM, 0);//协议族、socket类型、协议(0表示选择默认的协议)
//把socket设置为非阻塞方式
setnonblocking(listenfd);
int reuse_socket = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse_socket, sizeof(int)) == -1){
        printf("setsockopt reuse-addr error!");
    }
bzero(&serveraddr, sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
char local_addr[] = "0.0.0.0";
inet_aton(local_addr, &(serveraddr.sin_addr));//htons(SERV_PORT);
serveraddr.sin_port = htons(SERV_PORT);
bind(listenfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr));
listen(listenfd, LISTENQ);
maxi = 0;
}
void work_cycle(int j)
{
//生成用于处理accept的epoll专用的文件描述符
epfd = epoll_create(256);
//设置与要处理的事件相关的文件描述符
ev.data.fd = listenfd;
//设置要处理的事件类型
ev.events = EPOLLIN | EPOLLET;
//注册epoll事件
epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
for (;;)
{
//等待epoll事件的发生
nfds = epoll_wait(epfd, events, 20, 1000);
//处理所发生的所有事件
//printf("epoll_wait\n");
for (i = 0; i < nfds; ++i)
{
if (events[i].data.fd == listenfd)
{
connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &clilen);
if (connfd < 0)
{
printf("process %d:connfd<0 accept failure\n",j);
continue;
}
setnonblocking(connfd);
char *str = inet_ntoa(clientaddr.sin_addr);
//std::cout << "connec_ from >>" << str << std::endl;
 
printf("process %d:connect_from >>%s listenfd=%d connfd=%d\n",j, str,listenfd, connfd);
 
//设置用于读操作的文件描述符
 
ev.data.fd = connfd;
 
//设置用于注测的读操作事件
 
ev.events = EPOLLIN | EPOLLET;
 
//注册ev
 
epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
 
} else{
 
if (events[i].events & EPOLLIN)
 
{
 
printf("process %d:reading! connfd=%d\n",j,events[i].data.fd);
 
if ((sockfd = events[i].data.fd) < 0) continue;
data = (struct user_data *)malloc(sizeof(struct user_data));
if(data == NULL)
{
printf("process %d:user_data malloc error",j);
exit(1);
}
data->fd = sockfd;
 
if ((n = read(sockfd, data->line, MAXLINE)) < 0)
{
if (errno == ECONNRESET)
{
close(sockfd);
} else
printf("process %d:readline error\n",j);
if (data != NULL) {
free(data);
data = NULL;
}
}else {
if (n == 0)
{
close(sockfd);
printf("process %d:Client close connect!\n",j);
if (data != NULL) {
//delete data;
free(data);
data = NULL;
}
} else
{
data->n_size = n;
 
//设置需要传递出去的数据
 
ev.data.ptr = data;
 
//设置用于注测的写操作事件
 
ev.events = EPOLLOUT | EPOLLET;
 
//修改sockfd上要处理的事件为EPOLLOUT
 
epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
 
}
 
}
 
} else {
 
if (events[i].events & EPOLLOUT)
 
{
 
rdata = (struct user_data *) events[i].data.ptr;
 
sockfd = rdata->fd;
 
printf("process %d:writing! connfd=%d\n",j,sockfd);
 
write(sockfd, rdata->line, rdata->n_size);
 
//delete rdata;
 
free(rdata);
 
//设置用于读操作的文件描述符
 
ev.data.fd = sockfd;
 
//设置用于注测的读操作事件
 
ev.events = EPOLLIN | EPOLLET;
 
//修改sockfd上要处理的事件为EPOLIN
 
epoll_ctl(epfd, EPOLL_CTL_MOD, sockfd, &ev);
 
}
 
}
 
}
 
}
 
}
 
}
 
typedef void (*fun_ptr)(void);
 
void pxy_process()
 
{
 
printf("Hello,World!\n");
 
for(;;){
 
sleep(1);
 
//pxy_log_error(PXY_LOG_NOTICE,cycle->log,"sleep 1 second!\n");
 
}
 
exit(0);
 
}
 
int main()
 
{
 
int i;
 
int pid;
 
init();
 
for(i=0;i<3;i++)
{
pid = fork();
switch(pid){
case -1:
printf("fork sub process failed!\n");
break;
case 0:
work_cycle(i);
break;
default:
break;
}
}
while(1){
sleep(1);
}
}
