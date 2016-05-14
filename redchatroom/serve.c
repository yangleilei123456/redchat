#define USERMAX 256
#define FDSIZE 200
int socket_bind()
{
	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd != -1);
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family=AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&address.sin_addr);
	address.sin_port=htons(6000);
	int ret = bind(listenfd,(struct sockaddr *)&address,sizeof(address));
	assert(ret != -1);
	ret = listen(listenfd,10);
	assert(ret != -1);
	return listenfd;
}
void add_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events = state;
	ev.data.fd = fd;
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}
void hand_accept(int epollfd,int listenfd)
{
	struct sockaddr_in client;
	socklen_t cliaddrlen;
	int clientfd=accept(listenfd,(struct sockaddr*)&client,&cliaddrlen);
	assert(clientfd != -1);
	add_event(epollfd,clientfd,EPOLLIN);
}
void delete_event(int epollfd,int fd,int state)
{
	struct epoll_event ev;
	ev.events= state;
	ev.data.fd =fd;
	epoll_ctl(epollfd,EPOLL_CTL_DEL,fd,&ev);
}
bool parse_namepwd(char *buff)
{
	bool res = true;
	cJSON *root=cJSON_Parse(buff);
	cJSON* name1= cJSON_GetObjectItem(root,"usename");
	if(NULL ==name1)
	{
		printf("No name\n");
		res = false;
		return res;
	}
	char *name=name1->valuestring;
	cJSON *password1=cJSON_GetObjectItem(root,"password");
	if(NULL == password1)
	{
		printf("No password\n");
		res = false;
		return res;
	}
	char *password = password1->valuestring;
	res=check_Norepeat(name,password);
	if(!res)
	{
		printf("resgister failed,have existing\n");
	}
	return res;
}
void hand_data(int epollfd,int fd)
{
	char buff[128]={0};
	int num = read(fd,buff,128);
	if(num <= 0)
	{
		perror("read exception\n");
		close(fd);
		delete_event(epollfd,fd,NULL);
		return ;
	}
	if(buff[0] != '#')
	{
		//密文data;
		bool res=parse_namepwd(buff);
		if(res)
			buff="register successful";
		else
			buff="register failed";
		write(fd,buff,sizeof(buf));
		close(fd);
		delete_event(epollfd,fd,NULL);
		return ;
	}
	else 
	{
		//common data
	}
}
void hand_events(int epollfd,struct epoll_event *event,int num,int listenfd)
{
	int i=0;
	int fd;
	for(i=0;i<num;i++)
	{
		fd = event[i].data.fd;
		if((fd == listenfd)&&(event[i].events & EPOLLIN))
			hand_accept(epollfd,listenfd);
		else if(event[i].events & EPOLLIN)
			hand_data(epollfd,fd);
	}
}
void do_epoll(int listenfd)
{
	int epollfd;
	int ret;
	struct epoll_event events[USERMAX];
	epollfd = epoll_create(FDSIZE);
	add_event(epollfd,listenfd,EPOLLIN);
	while(1)
	{
		epoll_wait(epollfd,events,USERMAX,-1);
		ret = hand_events(epollfd,events,ret,listenfd);
	}
}
int main()
{
	int listenfd=socket_bind();
	do_epoll(listenfd);
	return 0;
}
