#ifndef YEE_H_
#define YEE_H_


struct hostent *gethost();

int getsocket();

void closesocket(int sockfd);

void init_sockaddr(struct sockaddr_in *sockaddr,struct hostent *host_global);

int getconnect(int sockfd,struct sockaddr_in *sockaddr);

int sencmd(int sockfd,char *cmd);

char * receivecmd(int sockfd);

char * receive_to_file(int sockfd,char *file);

char * link_deviceinfo(char *url,struct device *dev);

char * link_sensorinfo(char *url,struct sensors *sen);

char * link_numbersensorinfo(char *url,struct number_sensors *sen);

char * link_sensorinfo_notype(char *url,struct sensors *sen);

char * link_numbersensorinfo_notype(char *url,struct number_sensors *sen);

char * link_datapointinfo(char *tmps,char *file,int type);

char *link_photoinfo(char *url,char *file);

#endif
