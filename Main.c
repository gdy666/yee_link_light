#include "yeelight.h"
#include "yeeini.h"

extern int device_id;
extern int switch_id;
extern int yeelight;
struct switch_info *s_info=NULL;	//保存最后一次获取到的开关状态信息
pthread_mutex_t mutex;
/**
用于检测yeelink上的指定开关的状态，从而进行对灯的操纵。
**/
void yeelink_ser(){
	while(1){
		pthread_mutex_lock(&mutex);
		if(NULL==s_info){	//启动后第一次检测
			s_info=get_switch_info(device_id,switch_id);
			if(NULL==s_info){
				pthread_mutex_unlock(&mutex);
				continue;
			}else{
				change_light_state(s_info,yeelight);
			}

		}
		else{	
			struct switch_info *s_i=get_switch_info(device_id,switch_id);	//获取最新的开关信息
			if(NULL==s_i){
				pthread_mutex_unlock(&mutex);
				continue;
			}else if(strcmp(s_i->timestamp,s_info->timestamp)!=0){	//开关状态发生变化
				change_light_state(s_i,yeelight);
			}
			
			free(s_info->timestamp);
			free(s_info);
			s_info=s_i;
			
		}
		pthread_mutex_unlock(&mutex);
		usleep(800000); 
	}
};

/*
检测灯的状态，将灯的状态映射到yeelink的开关传感器
*/
void yeelight_ser(){
	int state;
	char* r;
	struct switch_info *s_i;
	
	while(1){
		sleep(10);
		pthread_mutex_lock(&mutex);
		state=check_light_state(yeelight);	//检测灯的状态
		s_i=get_switch_info(device_id,switch_id);	//获取最新的开关信息
		
		/*
			当灯的状态和当前yeelink的开关状态一致的时候不修改yeelink上的开关，
			目的是尽量减少状态的同步操作，防止冲突。
		*/
		if(s_i==NULL||
			state==ERROR||
			s_i->state==state)
		{
			if(NULL!=s_i){
				free(s_i->timestamp);
				free(s_i);
			}
			pthread_mutex_unlock(&mutex);
			continue;
		}
		
		r=change_switch_state(device_id,switch_id,state);	//同步状态
		free(r);
		free(s_i->timestamp);
		free(s_i);

		s_i=get_switch_info(device_id,switch_id);	//再次获取开关状态
		if(NULL!=s_i){
			s_info=s_i;
		}

		pthread_mutex_unlock(&mutex);
	}
};
int main(int argc,char *argv[])
{
	init_config();
	pthread_mutex_init (&mutex,NULL);
	pthread_t t_yeelink_ser,t_yeelight_ser;
	pthread_create(&t_yeelink_ser,NULL,(void*)yeelink_ser,NULL);
	pthread_create(&t_yeelight_ser,NULL,(void*)yeelight_ser,NULL);
	for(;;);
	return 0;
}
