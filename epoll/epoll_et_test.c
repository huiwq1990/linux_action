/**
 * http://www.cnblogs.com/charlesblc/p/5521086.html
 **/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <pthread.h>

#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>
#include <fcntl.h>

#define MAX_EVENT_NUMBER 1024
// 设置的比较小，为了方便测试输入大量数据，是否还会继续触发读
#define BUFFER_SIZE 10

int setnonblocking(int fd) {
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
        return old_option;
}

void addfd(int epollfd, int fd, bool enable_et) {
        epoll_event event;
        event.data.fd = fd;
        event.events = EPOLLIN;
        if (enable_et) {
                event.events |= EPOLLET;
        }
        epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
        setnonblocking(fd);
}

void lt(epoll_event *events, int number, int epollfd, int listenfd) {
        char buf[BUFFER_SIZE];
        for (int i=0; i<number; i++) {
                int sockfd = events[i].data.fd;
                if (sockfd == listenfd) {
                        sockaddr_in client_address;
                        socklen_t client_addrlen = sizeof(client_address);
                        int connfd = accept(listenfd, (sockaddr*)&client_address,
                                                &client_addrlen);
                        addfd(epollfd, connfd, false);
                }
                else if (events[i].events & EPOLLIN) {
                        printf("lt event trigger once\n");
                        memset(buf, '\0', BUFFER_SIZE);
                        int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                        if (ret <= 0) {
                                close(sockfd);
                                continue;
                        }
                        printf("get %d bytes of content: %s\n", ret, buf);
                }
                else {
                        printf("something else happened\n");
                }
        }
}

void et(epoll_event *events, int number, int epollfd, int listenfd) {
        char buf[BUFFER_SIZE];
        for (int i=0; i<number; i++) {
                int sockfd = events[i].data.fd;
                if (sockfd == listenfd) {
                        sockaddr_in client_address;
                        socklen_t client_addrlen = sizeof(client_address);
                        int connfd = accept(listenfd, (sockaddr*)&client_address,
                                                &client_addrlen);
                        addfd(epollfd, connfd, true);
                }
                else if(events[i].events & EPOLLIN) {
                        // Need to read complete
                        printf("et event trigger once\n");
                        // while(true) 会保证读完所有的数据
                        //while (true) {
                        //if(true) 模拟一次无法完全读取，观察et是否还会继续触发读
                        if (true) {
                                memset(buf, '\0', BUFFER_SIZE);
                                int ret = recv(sockfd, buf, BUFFER_SIZE-1, 0);
                                if (ret < 0) {
                                        // Below shows complete
                                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK)) {
                                                printf("read later\n");
                                                break;
                                        }
                                        printf("some error happens\n");
                                        close(sockfd);
                                        break;
                                }
                                else if (ret == 0) {
                                        close(sockfd);
                                        break;
                                }
                                else {
                                        printf("get %d bytes of content: %s\n", ret, buf);
                                }
                        }
                }
                else {
                        printf("something else happened\n");
                }
        }
}

int main(int argc, char *argv[]) {
        if (argc <= 1) {
                printf("usage: %s port_number ip_address\n", basename(argv[0]));
                return 1;
        }

        int port = atoi(argv[1]);
        int ret = 0;
        sockaddr_in address;
        bzero(&address, sizeof(address));
        address.sin_family = AF_INET;
        if (argc >= 3) {
                const char *ip =argv[2];
                inet_pton(AF_INET, ip, &address.sin_addr);
        }
        else {
                address.sin_addr.s_addr = INADDR_ANY;
        }
        address.sin_port = htons(port);

        int listenfd = socket(PF_INET, SOCK_STREAM, 0);
        assert(listenfd >= 0);

        ret = bind(listenfd, (sockaddr*)&address, sizeof(address));
        assert(ret != - 1);

        ret = listen(listenfd, 5);
        assert(ret != -1);

        epoll_event events[MAX_EVENT_NUMBER];
        int epollfd = epoll_create(5);
        assert(epollfd != -1);
        addfd(epollfd, listenfd, true);

        while(true) {
                ret = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);
                if (ret < 0) {
                        printf("epoll failure\n");
                        break;
                }
                // lt使用水平触发，et边缘触发
                lt(events, ret, epollfd, listenfd); // lt
                //et(events, ret, epollfd, listenfd); // et
        }

        close(listenfd);
        return 0;

}