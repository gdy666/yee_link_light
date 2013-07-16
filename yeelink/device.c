#include "../yeelink.h"
#include "yee.h"
extern char yeelink_apikey[];
char * create_device(struct device *dev){
	char *cmd;
	struct hostent *host=NULL;
	int sockfd;
	struct sockaddr_in sockaddr;
	host=gethost();
	if(NULL==host){
		return NULL;
	}
	sockfd=getsocket();
	if(-1==sockfd){
		return NULL;
	}
	init_sockaddr(&sockaddr,host);
	if(-1==(getconnect(sockfd,&sockaddr))){
		return NULL;
	}
	cmd=link_deviceinfo("/v1.0/devices",dev);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char * edit_device(int devid,struct device *dev){
	char device_id[30];
	char tmp_str[50];
	char *cmd;
	struct hostent *host=NULL;
	int sockfd;
	struct sockaddr_in sockaddr;
	host=gethost();
	if(NULL==host){
		return NULL;
	}
	sockfd=getsocket();
	if(-1==sockfd){
		return NULL;
	}
	init_sockaddr(&sockaddr,host);
	if(-1==(getconnect(sockfd,&sockaddr))){
		return NULL;
	}
	sprintf(device_id,"%d",devid);
	memset(tmp_str,0,sizeof(tmp_str));
	strcat(tmp_str,"/v1.0/device/");
	strcat(tmp_str,device_id);
	cmd=link_deviceinfo(tmp_str,dev);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *list_devices(){
	char cmd[MAXBUFF];
	char *ret;
	struct hostent *host=NULL;
	int sockfd;
	struct sockaddr_in sockaddr;
	host=gethost();
	if(NULL==host){
		return NULL;
	}
	sockfd=getsocket();
	if(-1==sockfd){
		return NULL;
	}
	init_sockaddr(&sockaddr,host);
	if(-1==(getconnect(sockfd,&sockaddr))){
		return NULL;
	}
	memset(cmd,0,sizeof(cmd));
	strcat(cmd,"GET /v1.0/devices HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: ");
	strcat(cmd,yeelink_apikey);
	strcat(cmd,"\r\n\r\n");
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(ret=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return ret;
}

char *show_device(int devid){
	char cmd[MAXBUFF];
	char device_id[30];
	char *ret;
	struct hostent *host=NULL;
	int sockfd;
	struct sockaddr_in sockaddr;
	host=gethost();
	if(NULL==host){
		return NULL;
	}
	sockfd=getsocket();
	if(-1==sockfd){
		return NULL;
	}
	init_sockaddr(&sockaddr,host);
	if(-1==(getconnect(sockfd,&sockaddr))){
		return NULL;
	}
	sprintf(device_id,"%d",devid);
	memset(cmd,0,sizeof(cmd));
	strcat(cmd,"GET /v1.0/device/");
	strcat(cmd,device_id);
	strcat(cmd," HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: ");
	strcat(cmd,yeelink_apikey);
	strcat(cmd,"\r\n\r\n");
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(ret=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return ret;
}

char *delete_device(int devid){
	char cmd[MAXBUFF];
	char device_id[30];
	char *ret;
	struct hostent *host=NULL;
	int sockfd;
	struct sockaddr_in sockaddr;
	host=gethost();
	if(NULL==host){
		return NULL;
	}
	sockfd=getsocket();
	if(-1==sockfd){
		return NULL;
	}
	init_sockaddr(&sockaddr,host);
	if(-1==(getconnect(sockfd,&sockaddr))){
		return NULL;
	}
	sprintf(device_id,"%d",devid);
	memset(cmd,0,sizeof(cmd));
	strcat(cmd,"DELETE /v1.0/device/");
	strcat(cmd,device_id);
	strcat(cmd," HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: ");
	strcat(cmd,yeelink_apikey);
	strcat(cmd,"\r\n\r\n");
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(ret=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return ret;
}
