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
	int sockfd = Socket("lbslife.baidu.com", 80);
	int length;
	printf("%d\n", sockfd );

	if (sockfd <= 0) {
		printf("socket conn fail");
		exit(1);
	}
	printf("%d ", sizeof(request));
	memset(request, 0, sizeof(request));

	strcat(request, "GET /shopmall/card/scenic/duhelper?uid=2a7a25ecf9cf13636d3e1bad HTTP/1.1\r\n");
	strcat(request, "Host: lbslife.baidu.com\r\n");
	strcat(request, "Content-Type: application/json\r\n");
	strcat(request, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\r\n");
	strcat(request, "Connection: close\r\n");
	int send = write(sockfd, request, strlen(request));
	printf("send result: %d ", send);



	printf("%s", request);


	do {
		memset(response, 0, sizeof(response));
		length = read(sockfd, response, sizeof(response));
		printf("read result: %d \n", length);

		// char * loc = strstr(response, "\r\n\r\n"); //截获返回头部，以\r\n\r\n为标识
		// if (loc) {
		// 	int loci = loc - response + 4;
		// 	write(1, response, loci);//如果是响应头部就打印至屏幕
		// 	write(file, loc, length - loci);//如果是响应主体就写入文件
		// } else {
		// 	write(file, response, length);
		// }
		printf("%s", response);
		if (length <= 0 ) //注意，因为之前采用的是close方法，也就是说一旦传输数据完毕，则服务器端会断开链接，则read函数会返回0，所以这里 会退出循环。如果采用的是Keep-Alive则服务器不关闭TCP链接，也就说程序将会被阻塞在read函数中，因此要注意的是自己判断是否读到了响应 的结尾，然后在再次调用read之前退出循环。
			break;
	} while (1);
printf("%s", response);
	close(sockfd);

	return 0;
}