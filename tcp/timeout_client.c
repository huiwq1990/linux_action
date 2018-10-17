#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
//超时连接
int timeout_connect(const char *ip, int port, int time);
 
int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s ip port\n", argv[0]);
		return 1;
	}
	
	const char *ip = argv[1];
	int port = atoi(argv[2]);
	
	int sockfd = timeout_connect(ip, port, 10);
	if (sockfd < 0)
		return 1;
	
	
	return 0;
}
 
int timeout_connect(const char *ip, int port, int time)
{
	int ret = 0;
	int error;
	
	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ip, &address.sin_addr);
	
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		return -1;
	
	//超时时间
	struct timeval timeout;
	timeout.tv_sec = time;
	timeout.tv_usec = 0;
	
	socklen_t len = sizeof(timeout);
	ret = setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, len);
	if (ret == -1) {
		error = errno;
		while ((close(sockfd) == -1) && (errno == EINTR));
		errno = error;
		return -1;
	}
	
	ret = connect(sockfd, (struct sockaddr*)&address, sizeof(address));
	if (ret == -1) {
		if (errno == EINPROGRESS) {
			printf("connecting timeout\n");
			return -1;
		}
		
		printf("error occur when connecting to server\n");
		return -1;
	}
	
	char buffer[1024];
	memset(buffer, '\0', 1024);
	ret = recv(sockfd, buffer, 1024, 0);
	
	printf("recv %d bytes, buf: %s\n", ret, buffer);
	
	return sockfd;
}
