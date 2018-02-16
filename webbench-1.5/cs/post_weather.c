#include<stdio.h>
#include "../socket.c"

#define MAXDATASIZE  500
#define REQUEST_SIZE 2048
#define RESPONSE_SIZE 40480

//http://www.sojson.com/open/api/weather/json.shtml?city=%E5%8C%97%E4%BA%AC
int main(int argc, char const *argv[])
{

	FILE *fp;

    fp = fopen("/tmp/json.txt", "w+");

	char buf[MAXDATASIZE];
	char request[REQUEST_SIZE] ;
	char response[RESPONSE_SIZE];
	char params[RESPONSE_SIZE];
	char tmp[RESPONSE_SIZE];

	int recvbytes;
	int sockfd = Socket("www.sojson.com", 80);
	int length,received;
	printf("%d\n", sockfd );

	if (sockfd <= 0) {
		printf("socket conn fail");
		exit(1);
	}
	printf("%ld ", sizeof(request));
	memset(request, '\0', sizeof(request));
	memset(response, '\0' ,sizeof(response));
	memset(params, '\0' ,sizeof(params));
	strcat(params, "a=1&b=2");
	
	printf("\n debug %ld %ld \n", strlen(request),sizeof(response));

	// strcat(request, "GET /shopmall/card/scenic/queryspotdetail?uid=3a0fbba8d2e061419ee32178 HTTP/1.1\r\n");
	strcat(request, "POST /open/api/weather/json.shtml?city=%E5%8C%97%E4%BA%AC HTTP/1.1\r\n");
	// strcat(request, "GET /shopmall/card/common/querylist?uid=62d852adf09e449a2fb17ef5&card=Scenic_Ar HTTP/1.1\r\n");
	strcat(request, "Host: www.sojson.com\r\n");
	sprintf(tmp, "Content-Length: %ld\r\n", strlen(params));
	strcat(request, tmp );
	strcat(request, "Connection: close\r\n");
	strcat(request, "\r\n");
	strcat(request, params);
	length = send(sockfd, request, strlen(request),MSG_WAITALL);
	printf("send result: %d \n", length);
	printf("%s \n", request);
	length = recv(sockfd,response,sizeof(response), MSG_WAITALL);
	printf("\n whole res ---------\n");
	printf("%s", response);

		printf("\n end res ---------\n");

	close(sockfd);

   fputs(response, fp);
   fclose(fp);

	return 0;
}