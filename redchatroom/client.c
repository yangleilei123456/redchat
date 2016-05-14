#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>
#include"cJSON.h"
typedef enum {true=1,false=0}bool;
void print()
{
	printf("		***********************\n");
	printf("	1:register()\n");
	printf("	2:login()\n");
	printf("		***********************\n");
}
int socket_bind()
{
	int sockfd;
	struct sockaddr_in ser;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(6000);
	inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);
	connect(sockfd,(struct sockaddr*)&ser,sizeof(ser));
	return sockfd;
}
void registe()
{
	int sockfd = socket_bind();

}
void login()
{

}
bool choose()
{
	bool res = true;
	printf("please choose (1 or 2)");
	int flag =0;
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:registe();break;
		case 2:login();break;
		default:printf("no choose\n"),res=false;break;
	}
	return res;
}
int main()
{
	while(1)
	{
		bool flag = choose();
		if(flag)
			break;
	}
	return 0;
}
