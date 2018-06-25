/******************************************
*项目：智能密码锁
*文件：smart2.c
*版本：2.0
*运行平台：华清远见F4412开发板
*作者：liyuan
*******************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/input.h>
#include "key.h"

#define INPUTTAG "/dev/input/event0"
#define LED_NUMS 4
#define BRIEF_LINES 4

typedef struct key {
	unsigned char key;
	char key_desc[30];
}key1_t;

key1_t table[] = {
 {KEY_POWER, "key power"},
 {KEY_VOLUMEDOWN, "key volume down"},
 {KEY_VOLUMEUP, "key volume up"},
};


extern int key_check()
{       int e=1;
	int i = 0;
	struct input_event ev;
	int fd = -1;
	if ((fd = open(INPUTTAG,O_RDWR|O_NONBLOCK))<0){
		perror("open error\n");
		exit(0);
	}
	while(e)
	{
		read(fd, &ev, sizeof(ev));
		switch(ev.type)
		{
		case EV_KEY:
		for (i = 0; i < (sizeof(table) / sizeof(table[0])); i++) 
            {
				if (table[i].key == ev.code) 
                                  {
					if (ev.value == 1)
                                          {
                                            
                                           e=0;
					    
                                          }				  
					
					else
					//	printf("%s is release\n", table[i].key_desc);
					break;
				}
			}
		default:
			break;
		}
	}
	close(fd);
	return 0;
}
