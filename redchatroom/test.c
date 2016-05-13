#include<string.h>
#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"cJSON.h"
char * create_json()
{
	cJSON *root;
	root = cJSON_CreateObject();
	if( root == NULL)
	{
		printf("createobject error\n");
		return ;
	}
	char buff[128]={0};
	printf("please input usename\n");
	fgets(buff,128,stdin);
	
	
	cJSON_AddStringToObject(root,"usename",buff);
	printf("please input password\n");
	fgets(buff,128,stdin);
	cJSON_AddStringToObject(root,"password",buff);
	char *s=cJSON_Print(root);
    cJSON_Delete(root);
	return s;
}
void parse(char *s)
{
	cJSON *root;
	root=cJSON_Parse(s);
	cJSON *name1=cJSON_GetObjectItem(root,"usename");
	if(name1 == NULL)
	{
		printf("No name!\n");
		return ;
	}
	char* name=name1->valuestring;
	cJSON *password1=cJSON_GetObjectItem(root,"password");
	if(password1 == NULL)
	{
		printf("No password!\n");
		return ;
	} 
	char* password=password1->valuestring;
	printf("%s",name);
	printf("%s",password);
	free(password);
	free(name);
}
int main()
{
	char *s=create_json();
	printf("%s\n",s);
	parse(s);
	free(s);
	return 0;
}

