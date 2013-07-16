#include "../yeelink.h"
#include "yee.h"
extern char yeelink_apikey[];

char *create_datapoints(int devid,int senid,char *file){
	char *cmd;
	char tmps[50];
	char tmps_1[30];
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
	strcat(tmps,"/v1.0/device/");
	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensor/");
	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",senid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/datapoints");

	cmd=link_datapointinfo(tmps,file,0);

	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *edit_datapoints(int devid,int senid,char *key,char *json_content){
	char *cmd;
	char tmps[100];
	char tmps_1[30];
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
	strcat(tmps,"/v1.0/device/");

	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensor/");

	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",senid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/datapoints/");
	strcat(tmps,key);

	cmd=link_datapointinfo(tmps,json_content,0);

	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(cmd=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return cmd;
}

char *show_datapoint(int devid,int senid,char *key){
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

	strcat(cmd,"/datapoints/");
	if(NULL!=key){
		strcat(cmd,key);
	}


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

char *delete_datapoint(int devid,int senid,char *key){
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

	strcat(cmd,"/datapoint/");
	strcat(cmd,key);

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

char *create_photo(int devid,int senid,char *photo){
	char *cmd;
	char tmps[50];
	char tmps_1[30];
	char *buff;
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
	strcat(tmps,"/v1.0/device/");
	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",devid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/sensor/");
	memset(tmps_1,0,sizeof(tmps_1));
	sprintf(tmps_1,"%d",senid);
	strcat(tmps,tmps_1);
	strcat(tmps,"/photos");

	cmd=link_photoinfo(tmps,photo);

	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(buff=receivecmd(sockfd))){
		return NULL;
	}
	closesocket(sockfd);
	return buff;
}

char *get_imageinfo(int devid,int senid,char *key){
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

	if(NULL!=key){
		strcat(cmd,"/photo/info/");
		strcat(cmd,key);
	}else{
		strcat(cmd,"/photo/info");
	}

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

char *get_image(int devid,int senid,char *key,char *file){
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

	if(NULL!=key){
		strcat(cmd,"/photo/content/");
		strcat(cmd,key);
	}else{
		strcat(cmd,"/photo/content");
	}

	strcat(cmd," HTTP/1.1\r\nHost: api.yeelink.net\r\nU-ApiKey: ");
	strcat(cmd,yeelink_apikey);
	strcat(cmd,"\r\n\r\n");

	if(-1==(sencmd(sockfd,cmd))){
		return NULL;
	}
	if(NULL==(ret=receive_to_file(sockfd,file))){
		return NULL;
	}
	closesocket(sockfd);
	return ret;
}
