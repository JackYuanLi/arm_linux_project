/******************************************
*项目：智能密码锁
*文件：smart2.c
*版本：2.0
*运行平台：华清远见F4412开发板
*作者：liyuan
*******************************************/
#include "buzzer.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
//定义音阶常量
#define b0 0
#define b1 262
#define b2 294
#define b3 330
#define b4 349
#define b5 392
#define b6 440
#define b7 494
//##################################
#define BUZZER_NUMS 1 

//#define BRIEF_LINES 4

#define BUZZINPUTTAG "/dev/input/event2"


char *buzzer_on = "1";
char *buzzer_off = "0";



extern void buzzer_sound(int numbers)
{
	int fd = -1;
	int ret;
	if ((fd = open(BUZZINPUTTAG,O_RDWR|O_NONBLOCK))<0){
		perror("open error\n");
		exit(0);
	}
	
	
	struct input_event event;
	event.type = EV_SND;
	event.code = SND_TONE;
	while (numbers>0) {
		//printf("enter any key to open the buzzer!\n");
		//getchar();
		event.value = 500;
		ret = write(fd,&event,sizeof(struct input_event));
		sleep(3);
		//printf("enter any key to close the buzzer!\n");
		//getchar();
		event.value = 0;
		ret = write(fd,&event,sizeof(struct input_event));
		numbers--;
	}

	close(fd);
	//return 0;
}

extern void buzzer_song(int number)
{   
    int i;
    int scale[61]={b3,b3,b3,b0,b3,b3,b3,b0,b3,b5,b1,b2,b3,b0,b4,b4,b4,b4,b0,b4,b3,b3,b3,b0,b3,b2,b2,b1,b2,b0,b5,b0,b3,b3,b3,b0,b3,b3,b3,b0,b3,b5,b1,b2,b3,b0,b4,b4,b4,b4,b0,b4,b3,b3,b3,b0,b5,b5,b4,b2,b1};         
	int fd=-1;
        int ret;
	if ((fd = open(BUZZINPUTTAG,O_RDWR|O_NONBLOCK))<0){
		perror("open error\n");
		exit(0);
	}
	
	
	struct input_event event;
	event.type = EV_SND;
	event.code = SND_TONE;
	while (number>0) {
		//262,294,330,349,392,440,494
		for(i=0;i<61;i++)
		{
			event.value = scale[i];
		    ret = write(fd,&event,sizeof(struct input_event));
			usleep(400000);
			event.value = 0;
		    ret = write(fd,&event,sizeof(struct input_event));
			//usleep(10000);
		}
		//sleep(3);
		
		event.value = 0;
		ret = write(fd,&event,sizeof(struct input_event));
		number--;
	}

	close(fd);
	//return 0;
}
