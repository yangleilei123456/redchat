#include"redchat.h"
void print()
{
	printf("****************************\n");
	printf("	1:register()\n");
	printf("	2:login()\n");
	printf("*****************************\n");
}
int socket_bind()
{
	int sockfd;
	struct sockaddr_in ser;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(6000);
	inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);
	int res = connect(sockfd,(struct sockaddr*)&ser,sizeof(ser));
	if(res < 0)
	{
		printf("connect failed\n");
		close(sockfd);
		return 1;
	}
	return sockfd;
}
bool register_namepwd(int sockfd)
{
	///////////////////////////////
	bool res = true;
	cJSON *root;
	root = cJSON_CreateObject();
	if(NULL == root)
	{ 
		printf("createobject error\n");
		res = false;
		return res;
	}
	printf("please input usename\n");
	char buff[128]={0};
	fgets(buff,128,stdin);
	printf("usename: %s",buff);
	cJSON_AddStringToObject(root,"usename",buff);
	printf("please input password\n");
	fgets(buff,128,stdin);
	printf("password: %s",buff);
	cJSON_AddStringToObject(root,"password",buff);
	char *s=cJSON_Print(root);
	strncpy(buff,s,128);
	write(sockfd,buff,strlen(buff));
	read(sockfd,buff,128);
	if(strcmp(buff,"no") == 0)
	{
		res=false;
		printf("register failed\n");
	} 
	else if(strcmp(buff,"yes")==0)
	{
		printf("register successful,please login\n");
	}
	cJSON_Delete(root);
	free(s);
	return res;
}
bool registe()
{
	////////////////////////////////
	bool res = true;
	int sockfd = socket_bind();
	if(sockfd == 1)
	{ 
		res = false;
		return res;
	}
	res = register_namepwd(sockfd);
	return res;
}
bool login()
{
	bool res = true;
	return res;
}
bool choose()
{
	print();
	bool res = true;
	printf("please choose (1 or 2)\n");
	int flag =0;
	scanf("%d",&flag);
	getchar();//清掉回车
	switch(flag)
	{
		case 1:res=registe();break;
		case 2:res=login();break;
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
