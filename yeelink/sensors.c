#include "../yeelink.h"
#include "yee.h"
extern char yeelink_apikey[];
char *create_sensors(struct sensors *sen,int devid){
	char *cmd;
	char tmps[50];
	char tmps_1[50];
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
	memset(tmps,0,sizeof(tmps));
	memset(tmps_1,0,sizeof(tmps_1));
	strcat(tmps,"/v1.0/device/");
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensors");
	cmd=link_sensorinfo(tmps,sen);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *create_numbersensors(struct number_sensors *sen,int devid){
	char *cmd;
	char tmps[50];
	char tmps_1[50];
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
	memset(tmps,0,sizeof(tmps));
	memset(tmps_1,0,sizeof(tmps_1));
	strcat(tmps,"/v1.0/device/");
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensors");
	cmd=link_numbersensorinfo(tmps,sen);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *edit_sensors(int devid,int senid,struct sensors *sen){
	char *cmd;
	char tmps[50];
	char tmps_1[50];
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
	memset(tmps,0,sizeof(tmps));
	memset(tmps_1,0,sizeof(tmps_1));
	strcat(tmps,"/v1.0/device/");
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensor/");
	sprintf(tmps_1,"%d",senid);
	strcat(tmps,tmps_1);
	cmd=link_sensorinfo_notype(tmps,sen);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *edit_number_sensors(int devid,int senid,struct number_sensors *sen){
	char *cmd;
	char tmps[50];
	char tmps_1[50];
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
	memset(tmps,0,sizeof(tmps));
	memset(tmps_1,0,sizeof(tmps_1));
	strcat(tmps,"/v1.0/device/");
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensor/");
	sprintf(tmps_1,"%d",senid);
	strcat(tmps,tmps_1);
	cmd=link_numbersensorinfo_notype(tmps,sen);
	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *list_sensors(int devid){
	char cmd[MAXBUFF];
	char tmps[50];
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
	memset(tmps,0,sizeof(tmps));
	strcat(cmd,"GET /v1.0/device/");
	sprintf(tmps,"%d",devid);
	strcat(cmd,tmps);
	strcat(cmd,"/sensors HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: ");
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

char *show_sensor(int devid,int senid){
	char cmd[MAXBUFF];
	char tmps[50];
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
	memset(tmps,0,sizeof(tmps));
	strcat(cmd,"GET /v1.0/device/");
	sprintf(tmps,"%d",devid);
	strcat(cmd,tmps);
	strcat(cmd,"/sensor/");
	memset(tmps,0,sizeof(tmps));
	sprintf(tmps,"%d",senid);
	strcat(cmd,tmps);
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

char *delete_sensors(int devid,int senid){
	char cmd[MAXBUFF];
	char tmps[50];
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
	memset(tmps,0,sizeof(tmps));
	strcat(cmd,"DELETE /v1.0/device/");
	sprintf(tmps,"%d",devid);
	strcat(cmd,tmps);
	strcat(cmd,"/sensor/");
	memset(tmps,0,sizeof(tmps));
	sprintf(tmps,"%d",senid);
	strcat(cmd,tmps);
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
