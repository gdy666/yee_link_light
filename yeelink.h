#ifndef __YEELINK
#define __YEELINK

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include <pthread.h>

#define HOST_NAME "api.yeelink.net"
#define PORT 80
#define MAXBUFF 1024


/**
 * 设备数据结构
 * */
struct device{
	char *title;
	char *about;
	char *tags;
	char *local;
	float latitude;
	float longitude;
};

/**
 * 通用传感器
 * */
struct sensors{
	char *type;
	char *title;
	char *about;
	char *tags;
};

/**
 * 数值传感器
 * */
struct number_sensors{
	struct sensors *sensors;
	char *name;
	char *symbol;
};



/**
 * 创建设备
 * */
char * create_device(struct device *dev);

/**
 * 编辑设备
 * */
char * edit_device(int devid,struct device *dev);

/**
 * 罗列设备
 * */
char *list_devices();

/**
 * 查看设备
 * */
char *show_device(int devid);

/**
 * 删除设备
 * */
char *delete_device(int devid);

/**
 * 创建普通传感器
 * */
char *create_sensors(struct sensors *sen,int devid);

/**
 * 创建数值型传感器
 * */
char *create_numbersensors(struct number_sensors *sen,int devid);

/**
 * 编辑普通传感器
 * */
char *edit_sensors(int devid,int senid,struct sensors *sen);
/**
 * 编辑数值传感器
 * */
char *edit_number_sensors(int devid,int senid,struct number_sensors *sen);

/**
 * 罗列传感器
 * */
char *list_sensors(int devid);

/**
 * 查看传感器
 * */
char *show_sensor(int devid,int senid);

/**
 * 删除传感器
 * */
char *delete_sensors(int devid,int senid);

/**
 * 创建数据点
 * */
char *create_datapoints(int devid,int senid,char *file);

/**
 * 编辑数据点
 * */
char *edit_datapoints(int devid,int senid,char *key,char *file);

/**
 * 查看数据点
 * */
char *show_datapoint(int devid,int senid,char *key);

/**
 * 删除数据点
 * */
char *delete_datapoint(int devid,int senid,char *key);

/**
 * 增加图片   In test.
 * */
//char *create_photo(int devid,int senid,char *photo);

/**
 * 获取图像信息
 * */
char *get_imageinfo(int devid,int senid,char *key);

/**
 * 获取图像内容  In test.
 * */
//char *get_image(int devid,int senid,char *key,char *file);

#endif
