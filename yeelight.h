#ifndef _YEELIGHT_H
#define _YEELIGHT_H

#include "yeelink.h"



#define CLOSED 0
#define OPENED 1
#define ERROR -1
#define OFFLINE -2

//传感器（开关）信息
struct switch_info{
	char* timestamp;
	int state;
};


/**
获取开关状态 CLOSED:关闭 OPENED：打开 ERROR：未知错误
**/
struct switch_info* get_switch_info(int devid,int senid);	

/**
改变开关状态
**/
char* change_switch_state(int devid,int senid,int state);

/**
查询灯的状态： 开启|关闭|离线
**/
int check_light_state(int id);

/**
根据switch_info开关信息改变灯的状态
**/
void change_light_state(struct switch_info*,int);
#endif
