#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
void print()
{
	printf("		***********************\n");
	printf("	1:register()\n");
	printf("	2:login()\n");
	printf("		***********************\n");
}
bool choose()
{
	bool res = true;
	printf("please choose (1 or 2)");
	int flag =0;
	scanf("%d",&flag);
	switch(flag)
	{
		case 1:register();break;
		case 2:login();break;
		default:printf("no choose\n"),res=false;break;
	}
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
