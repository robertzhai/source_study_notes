#include<stdio.h>
#include "../socket.c"

#define MAXDATASIZE  3000
#define REQUEST_SIZE 2048

//http://www.sojson.com/open/api/weather/json.shtml?city=%E5%8C%97%E4%BA%AC
int main(int argc, char const *argv[])
{

	char buf[MAXDATASIZE];
	char request[REQUEST_SIZE] ;
	char response[REQUEST_SIZE];
	int recvbytes;
	int sockfd = Socket("github.com", 80);
	int length;
	printf("%d\n", sockfd );

	if (sockfd <= 0) {
		printf("socket conn fail");
		exit(1);
	}
	printf("%ld ", sizeof(request));
	memset(request, '\0', sizeof(request));

	strcat(request, "GET / HTTP/1.1\r\n");
	strcat(request, "Host: github.com\r\n");
	strcat(request, "Connection: close\r\n");
	strcat(request, "\r\n");
	int send = write(sockfd, request, strlen(request));
	printf("send result: %d ", send);
	printf("%s \n", request);

	do {
		memset(response, '\0' ,sizeof(response));
		length = read(sockfd, response, sizeof(response) - 1);
		printf("read result: %d \n", length);
		printf("%s", response);
		if (length <= 0 ) 
			break;
	} while (1);
	
	printf("%s", response);
	close(sockfd);

	return 0;
}