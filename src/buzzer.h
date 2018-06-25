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

extern void buzzer_sound(int numbers);
extern void buzzer_song(int number);