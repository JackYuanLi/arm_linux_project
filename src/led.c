/******************************************
*项目：智能密码锁
*文件：smart2.c
*版本：2.0
*运行平台：华清远见F4412开发板
*作者：liyuan
*******************************************/
#include "led.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define LED_NUMS 4
char *led_path[LED_NUMS] = {"/sys/class/leds/led2/brightness",
							"/sys/class/leds/led3/brightness",
							"/sys/class/leds/led4/brightness",
							"/sys/class/leds/led5/brightness"};

char *ledon = "1";
char *ledoff = "0";

extern void led_right(int numbers,int time)
{
	int fd[LED_NUMS] = {0};
	int i;	
	for (i = 0; i < LED_NUMS; i++) {
		if ((fd[i] = open(led_path[i], O_RDWR)) == -1) {
			perror("open led error\n");
			exit(EXIT_FAILURE);	
		}
	}
	//draw_string(brief, BRIEF_LINES);
	while (numbers>0) {
		for (i = 0; i < LED_NUMS; i++) {
			write(fd[i], ledon, 1);
		}
		sleep(time);
		for (i = 0; i < LED_NUMS; i++) {
			write(fd[i], ledoff, 1);
		}
		sleep(time);
		numbers--;
	}

	
}
