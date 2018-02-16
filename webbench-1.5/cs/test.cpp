#include <netinet/in.h>
#include<cstdio>

int main(int argc, char const *argv[])
{
	sockaddr s1;
	sockaddr_in s2;
	in_addr s3;
	int a ;
	long b;
	unsigned long addr;

	printf("%ld %ld %ld ", sizeof(s1),sizeof(s2),sizeof(s3));

	return 0;
}