#include "../yeelink.h"
extern char yeelink_apikey[];
struct hostent *gethost(){
	struct hostent *host_global=NULL;
	if(NULL==(host_global=gethostbyname(HOST_NAME))){
		herror("host");
		return NULL;
	}
	return host_global;
}

int getsocket(){
	int sockfd;
	if(-1==(sockfd=socket(AF_INET,SOCK_STREAM,0))){
		perror("socket");
		return -1;
	}
	return sockfd;
}

void closesocket(int sockfd){
	close(sockfd);
}

void init_sockaddr(struct sockaddr_in *sockaddr,struct hostent *host_global){
	char buff[30];
	sockaddr->sin_family=AF_INET;
	sockaddr->sin_port=htons(PORT);
	sockaddr->sin_addr.s_addr=inet_addr(inet_ntop(host_global->h_addrtype,host_global->h_addr,buff,sizeof(buff)));
	memset(sockaddr->sin_zero,0,sizeof(sockaddr->sin_zero));
}

int getconnect(int sockfd,struct sockaddr_in *sockaddr){
	if(-1==(connect(sockfd,(struct sockaddr*)(sockaddr),sizeof(struct sockaddr)))){
		perror("connect");
		return -1;
	}
	return 0;
}

int sencmd(int sockfd,char *cmd){
	if(-1==(send(sockfd,cmd,strlen(cmd),0))){
		perror("send");
		return -1;
	}
	return 0;
}

char * receivecmd(int sockfd){
	//char buff_2[MAXBUFF*10];
	char *buff_2=(char*)malloc(sizeof(char)*MAXBUFF*10);
	memset(buff_2,0,sizeof(buff_2));
	
	if(-1==(recv(sockfd,buff_2,MAXBUFF*10,0))){
		perror("receive");
		free(buff_2);
		return NULL;
	}
	return buff_2;
}

int logfile(char *p,char *file){
	FILE *fp;
	if(NULL==(fp=fopen(file,"a+"))){
		puts("Open file error!");
		return 0;
	}
	fprintf(fp,"%s",p);
	fclose(fp);
	return 1;
}

char * receive_to_file(int sockfd,char *file){
	char buff_2[MAXBUFF+1];
	FILE *fp;
	int len;
	if(NULL==(fp=fopen(file,"wb"))){
		puts("File can not open!");
		return NULL;
	}
	fclose(fp);
	do{
		memset(buff_2,0,sizeof(buff_2));
		len=recv(sockfd,buff_2,MAXBUFF,0);
		logfile(buff_2,file);
	}while(len!=0);
	return file;
}

char * link_deviceinfo(char *url,struct device *dev){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	int tmplen;
	int i;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");

	memset(buff,0,sizeof(buff));
	strcat(buff,"{\"title\":\"");
	/*
ENTERNAME:
	puts("Please enter device name: ");
	gets(tmps);
	tmplen=strlen(tmps);
	if(tmplen<1){
		puts("name too short!");
		goto ENTERNAME;
	}else if(tmplen>30){
		puts("name too long!");
		goto ENTERNAME;
	}
	*/
	strcat(buff,dev->title);
	strcat(buff,"\",\"about\":\"");
	/*
ENTERDESC:
	puts("Please enter some infomation about the device: ");
	gets(tmps);
	tmplen=strlen(tmps);
	if(tmplen>30){
		puts("description too long!");
		goto ENTERDESC;
	}
	*/
	strcat(buff,dev->about);
	strcat(buff,"\",\"tags\":[\"");
	/*
ENTERTAGS:
	puts("Pleater tags,seperate with \",\": ");
	gets(tmps);
	if(strlen(tmps)<=0){
		puts("Tags too short!");
		goto ENTERTAGS;
	}
	if(tmps[strlen(tmps)-1]==','){
		puts("You can not end with \",\"");
		goto ENTERTAGS;
	}
	*/
	i=0;
	tmplen=strlen(buff);
	while(dev->tags[i]!='\0'){
		if(dev->tags[i]==','){
			strcat(buff,"\",\"");
			i++;
			tmplen+=3;
			continue;
		}
		buff[tmplen++]=dev->tags[i++];
	}
	buff[tmplen]='\0';
	strcat(buff,"\"],\"location\":{\"local\":\"");
	/*
ENTERLOCATION:
	puts("Please enter your location: ");
	gets(tmps);
	tmplen=strlen(tmps);
	if(tmplen<=0){
		puts("Location too short!");
		goto ENTERLOCATION;
	}
	*/
	strcat(buff,dev->local);
	strcat(buff,"\",\"latitude\":");
	/*
ENTERLATITUDE:
	puts("Please enter latitude: ");
	gets(tmps);
	tmplen=strlen(tmps);
	if(tmps<=0){
		puts("Latitude too short!");
		goto ENTERLATITUDE;
	}
	*/
	sprintf(tmps,"%f",dev->latitude);
	strcat(buff,tmps);
	strcat(buff,",\"longitude\":");
	/*
ENTERLONGITUDE:
	puts("Please enter latitude: ");
	gets(tmps);
	tmplen=strlen(tmps);
	if(tmps<=0){
		puts("Latitude too short!");
		goto ENTERLONGITUDE;
	}
	*/
	sprintf(tmps,"%f",dev->longitude);
	strcat(buff,tmps);
	strcat(buff,"}}");

	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char * link_sensorinfo(char *url,struct sensors *sen){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	int tmplen;
	int i;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");

	memset(buff,0,sizeof(buff));
	strcat(buff,"{\"type\":\"");
	strcat(buff,sen->type);
	strcat(buff,"\",\"title\":\"");
	strcat(buff,sen->title);
	strcat(buff,"\",\"about\":\"");
	strcat(buff,sen->about);
	strcat(buff,"\",\"tags\":[\"");
	i=0;
	tmplen=strlen(buff);
	while(sen->tags[i]!='\0'){
		if(sen->tags[i]==','){
			strcat(buff,"\",\"");
			i++;
			tmplen+=3;
			continue;
		}
		buff[tmplen++]=sen->tags[i++];
	}
	buff[tmplen]='\0';
	strcat(buff,"\"]}");

	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char * link_numbersensorinfo(char *url,struct number_sensors *sen){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	int tmplen;
	int i;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");

	memset(buff,0,sizeof(buff));
	strcat(buff,"{\"type\":\"");
	strcat(buff,sen->sensors->type);
	strcat(buff,"\",\"title\":\"");
	strcat(buff,sen->sensors->title);
	strcat(buff,"\",\"about\":\"");
	strcat(buff,sen->sensors->about);
	strcat(buff,"\",\"tags\":[\"");
	i=0;
	tmplen=strlen(buff);
	while(sen->sensors->tags[i]!='\0'){
		if(sen->sensors->tags[i]==','){
			strcat(buff,"\",\"");
			i++;
			tmplen+=3;
			continue;
		}
		buff[tmplen++]=sen->sensors->tags[i++];
	}
	buff[tmplen]='\0';
	strcat(buff,"\"],\"unit\":{\"name\":\"");
	strcat(buff,sen->name);
	strcat(buff,"\",\"symbol\":\"");
	strcat(buff,sen->symbol);
	strcat(buff,"\"}}");

	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char * link_sensorinfo_notype(char *url,struct sensors *sen){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	int tmplen;
	int i;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");

	memset(buff,0,sizeof(buff));
	strcat(buff,"{\"title\":\"");
	strcat(buff,sen->title);
	strcat(buff,"\",\"about\":\"");
	strcat(buff,sen->about);
	strcat(buff,"\",\"tags\":[\"");
	i=0;
	tmplen=strlen(buff);
	while(sen->tags[i]!='\0'){
		if(sen->tags[i]==','){
			strcat(buff,"\",\"");
			i++;
			tmplen+=3;
			continue;
		}
		buff[tmplen++]=sen->tags[i++];
	}
	buff[tmplen]='\0';
	strcat(buff,"\"]}");

	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char * link_numbersensorinfo_notype(char *url,struct number_sensors *sen){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	int tmplen;
	int i;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");

	memset(buff,0,sizeof(buff));
	strcat(buff,"{\"title\":\"");
	strcat(buff,sen->sensors->title);
	strcat(buff,"\",\"about\":\"");
	strcat(buff,sen->sensors->about);
	strcat(buff,"\",\"tags\":[\"");
	i=0;
	tmplen=strlen(buff);
	while(sen->sensors->tags[i]!='\0'){
		if(sen->sensors->tags[i]==','){
			strcat(buff,"\",\"");
			i++;
			tmplen+=3;
			continue;
		}
		buff[tmplen++]=sen->sensors->tags[i++];
	}
	buff[tmplen]='\0';
	strcat(buff,"\"],\"unit\":{\"name\":\"");
	strcat(buff,sen->name);
	strcat(buff,"\",\"symbol\":\"");
	strcat(buff,sen->symbol);
	strcat(buff,"\"}}");

	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char * link_datapointinfo(char *url,char *json_content,int type){
	//char post_cmd[MAXBUFF];
	char *post_cmd=(char*)malloc(sizeof(char)*MAXBUFF);
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	//int tmplen;
	int i;
	//FILE *fp;
	//char c;
	memset(post_cmd,0,sizeof(post_cmd));
	if(type==0){
		strcat(post_cmd,"POST ");
	}else if(type==1){
		strcat(post_cmd,"PUT ");
	}else{
		printf("The method is : %d\n",type);
	}
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: application/x-www-form-urlencoded\r\n");


	memset(buff,0,sizeof(buff));
	i=0;
	char *c=json_content;
	while(*c!='\0'){
		if(*c=='\n'||*c==' '||*c=='\r'){
			c++;
			continue;
		}
		buff[i++]=*c;
		c++;
	}
	buff[i]='\0';
	sprintf(tmps,"%d",strlen(buff));
	strcat(post_cmd,"Content-Length: ");
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\n\r\n");
	strcat(post_cmd,buff);

	return post_cmd;
}

char *link_photoinfo(char *url,char *file){
	char post_cmd[MAXBUFF];
	char *cmd;
	char buff[MAXBUFF];
	char tmps[MAXBUFF/4];
	//char picture[MAXBUFF*101];
	char* picture=(char*)malloc(sizeof(char)*MAXBUFF*101);
	int i;
	FILE *fp;
	//int f;
	//int tmp;
	char c;
	//int tmp_len;
	long long file_len;
	memset(post_cmd,0,sizeof(post_cmd));
	strcat(post_cmd,"POST ");
	strcat(post_cmd,url);
	strcat(post_cmd,"  HTTP/1.1\r\nHost: api.yeelink.net\r\n");
	strcat(post_cmd,"U-ApiKey: ");
	strcat(post_cmd,yeelink_apikey);
	strcat(post_cmd,"\r\n");
	strcat(post_cmd,"Content-Type: multipart/form-data; boundary=--agcsascvascascasca\r\n");
	strcat(post_cmd,"Content-Length: ");
	/**
	 * 加上图片长度，暂时没加上
	 * */
	/////////////////////
	if(NULL==(fp=fopen(file,"rb"))){
		puts("File can not open!");
		return NULL;
	}
	i=0;
	fseek(fp,0,SEEK_END);//指针移动到文件末尾
	file_len=ftell(fp);
	fclose(fp);
	sprintf(tmps,"%lld",file_len);
	strcat(post_cmd,tmps);
	strcat(post_cmd,"\r\nConnection: Keep-Alive");
	/////////////////////
	strcat(post_cmd,"\r\n\r\n");

	memset(buff,0,sizeof(tmps));
	strcat(buff,"--agcsascvascascasca\r\n");
	strcat(buff,"Content-Disposition: form-data; name=\"data\" ");
	strcat(buff,"filename=\"");
	strcat(buff,file);
	strcat(buff,"\"\r\n");
	strcat(buff,"Content-Type: application/octet-stream");
	strcat(buff,"\r\n\r\n");
	/**
	 * 加上图片内容
	 * */
	///////////////////////////
	strcat(post_cmd,buff);
	memcpy(picture,post_cmd,sizeof(post_cmd));
	file_len=strlen(picture)+MAXBUFF;
	fp=fopen(file,"rb");
	while(!feof(fp)){
		c=fgetc(fp);
		picture[file_len++]=c;
		//memcpy(&(picture[file_len]),buff,tmp);
		//file_len+=tmp;
	}
	fclose(fp);
	//memcpy(&(picture[file_len]),buff,tmp);
	//file_len+=tmp;
	///////////////////////////
	//strcat(buff,"\r\n--agcsascvascascasca\r\n");
	cmd="\r\n--agcsascvascascasca\r\n";
	memcpy(&(picture[file_len]),cmd,sizeof(cmd));

	//strcat(post_cmd,buff);

	return picture;
}
