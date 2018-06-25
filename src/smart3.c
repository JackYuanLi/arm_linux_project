/******************************************
*项目：智能密码锁
*文件：smart2.c
*版本：2.0
*运行平台：华清远见F4412开发板
*作者：liyuan
*******************************************/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
//#######################################
#include "led.h"
#include "buzzer.h"
#include "key.h"

extern int key_check();
extern void led_right(int numbers,int time);
extern void buzzer_sound(int numbers);
extern void buzzer_song(int number);
char result[20];
//########################################
char uname[20];
char pawd[20];
int work_mode;
char *path;
char *strcat(char *dest,const char *src);
char *path1="admin.txt";

//##############################################

//写入初始密码
void write_file(int fd)
    {
	    char buf[20]="abcde";
	    write(fd,buf,sizeof(buf));
        close(fd);
    }
//##############################################

//修改密码
void change_pw(char new_pw[20])
    {
		int fd;
		//char *path="test1.txt";
		fd=open(path,O_WRONLY);
		write(fd,new_pw,(sizeof(new_pw)+1));
		close(fd);
		printf("##################################################\n");
		printf("Change success!\n");
    }
//##############################################

//修改管理员密码
void change_pw1(char new_pw[20])
    {
		int fd;
		//char *path1="admin.txt";
		fd=open(path1,O_WRONLY);
		write(fd,new_pw,(sizeof(new_pw)+1));
		close(fd);
		printf("##################################################\n");
		printf("Change success!\n");
    }
//##############################################

//读取密码文件内容
char read_file()
    {
	    int fd;
		//char *path="test1.txt";
	    //char result[20];
	    fd=open(path,O_RDONLY);
		read(fd,result,10);
		//printf("The content is %s",result);
						
		close(fd);
	    //return *result;
    }
//##############################################

//读取管理员密码文件内容
char read_file1()
    {
	    int fd;
	    fd=open(path1,O_RDONLY);
	    read(fd,result,10);				
	    close(fd);
	    
    }

//初始新建密码文件
int create_file()
   {
	 int fd;
     //char *path="test1.txt";
	 fd=creat(path1,00777);
	 return fd;
   }
//######################################################

//密码对比
static int password_check( char *cur_passwd, char *corr_passwd)
{
		int flag;
		if(strcmp(cur_passwd,corr_passwd)==0)
		  {
				flag=1;
		  }
		else
		  {
				flag=0;
		  }
					
		return flag;
}
//#########################################################

//秒延时
void delay(int a)
    {
       unsigned char b;
	   for(b=255;b>0;b--)
	      {
		    a--;
		  }

    }
//#########################################################

//分钟延时
void delay_minute(int a)
    {
       unsigned char b;
	   for(b=255;b>0;b--)
	     {
		   for(;a>0;a--)
		     {
				 delay(1000);
			 }	 
		 }
 
    }
//#########################################################

//检查文件是否存在
int check_file(const char *file_path)
   {   
	   int flag=0;
	   if(file_path==NULL)
	      flag=0;
	   if(access(file_path,F_OK)==0)
		  flag=1;
	   return flag;
   }								
//###################################################

//创建新用户
void create_new_user()
{     int fd;
      printf("##################################################\n");
	  printf("Please input new user name:");
      scanf("%s",uname);
      sleep(1);
	  printf("##################################################\n");
      printf("Please input new user password:");
      scanf("%s",pawd);
      path=uname;
      strcat(path,".txt");
	  fd=creat(path,00777);
	  write(fd,pawd,sizeof(pawd));
	  close(fd);
	  printf("##################################################\n");
	  printf("creat success!\n");
	  
}
//#######################################################

//用户模式
void user()
{
//Please_try_again:
int b,c;
int file_flag=0;
int flags=0;
int count=0;
char *user_password,new_pw[20],y_n[1];
char a[20];
char *results;
Please_try_again:
file_flag=check_file(path);

if(file_flag==0)
  {    
       printf("##################################################\n");
       printf("No user\n");
       goto quit;
	   //create_file();
      //write_file(create_file());
  }
 
user_password=pawd;
 
while(count<4)
{   
    printf("##################################################\n");
	printf("Please input the password:\n");
	scanf("%s",pawd);
	read_file();
	results=result;
	flags=password_check(user_password,results);
	if(flags)
     {   
         printf("##################################################\n");
  	     printf("Password right,please wait open the door!\n");
         delay(10);
		 led_right(3,1);
         buzzer_song(1);
         //打开门操作
		 printf("##################################################\n");
         printf("Do you want change the password(y)or(n):");
         scanf("%s",y_n);
		 if(y_n[0]=='y')
         {   
	         printf("##################################################\n");
             printf("Please input the new password:");
	         scanf("%s",new_pw);
	         change_pw(new_pw);
			 y_n[0]='n';
         }
                else
              {   
		          printf("##################################################\n");
                  printf("你想离开吗？离开(1),继续(2):");
                  scanf("%d",&b);
                  if(b==1)
                  {    
                       b=0;
                       goto quit;
                  }
              }
      }
     else
       { 
         printf("##################################################\n");
   	     printf("The password error!!!\n");
	     sleep(1);
		 buzzer_sound(1);
		 printf("##################################################\n");
	     printf("Please try again\n");
	     count++;
       }
	 
}

if(count==4)
	count=0;
printf("##################################################\n");
printf("Please wait 1 minutes,try again!\n");
buzzer_sound(3);
sleep(10);
quit:
printf("##################################################\n");
printf("你想退出本用户吗？是(1),否(2):");
scanf("%d",&c);
if(c==2)
   {
    c=0;
   goto Please_try_again;
   }
}
//##################################################

//管理模式
void admin()
{   int c;
    int flags=0;
    int count=0;
    char user_password[20],new_pw[20],y_n[1];
    char a[20];
    char *results;
    int file_flag=0;
	Please_try_again:
	file_flag=check_file(path1);
	if(file_flag==0)
  {
      create_file();
      write_file(create_file());
  }
  while(count<4)
{   
    printf("##################################################\n");
	printf("Please input the password:\n");
	scanf("%s",user_password);
	read_file1();
	results=result;
	flags=password_check(user_password,results);
	if(flags)
     {   
         printf("##################################################\n");
  	     printf("Password right,please wait open the door!\n");
         delay(10);
		 led_right(3,1);
		 buzzer_song(1);
         //打开门操作
		 printf("##################################################\n");
         printf("你可以选择修改密码(y),创建新用户(c),离开(q)");
         scanf("%s",y_n);
		 if(y_n[0]=='y')
         {   
	         printf("##################################################\n");
             printf("Please input the new password:");
	         scanf("%s",new_pw);
	         change_pw1(new_pw);
			 y_n[0]='0';
         }
		 if(y_n[0]=='c')
		 {
			 create_new_user();
		 }
		 if(y_n[0]=='q')
		 {
			 goto quit1;
		 }
      }
     else
       { 
         printf("##################################################\n");
   	     printf("The password error!!!\n");
	     sleep(1);
		 buzzer_sound(1);
		 printf("##################################################\n");
	     printf("Please try again\n");
	     count++;
       }
	 
}

if(count==4)
	count=0;
printf("##################################################\n");
printf("Please wait 1 minutes,try again!\n");
buzzer_sound(3);
sleep(10);
quit1:
printf("##################################################\n");
printf("你想退出管理模式吗？是(1),否(2):");
scanf("%d",&c);
if(c==2)
   {
    c=0;
   goto Please_try_again;
   }

	
}
//########################################################################

//功能选择菜单
 int menu_show(void)
{   
    int work_mode_num,a,b;
	printf("##############################################\n");
	printf("#           ********************             #\n");
	printf("#           *欢迎来到创新工厂！*             #\n");
	printf("#           ********************             #\n");
	printf("##############################################\n");
	printf("# <1> .用户模式                              #\n");
	printf("# <2> .管理模式                              #\n");
	printf("# <3> .帮助？                                #\n");
	printf("# 请选择您需要的功能,输入：1、2、3           #\n");
	printf("#>>>:");
	while(1)
	{
		scanf("%d", &a);
		getchar();
		if(a >= 1 && a <= 4)
		{
			work_mode_num= a;
			break;
		}
		else
		{
			printf("# 输入错误，请重新输入！                      #\n");
			printf("#                                             #\n");
			printf("#>>>:");
		}
	}
	return work_mode_num;
    
}
//###################################################################

//帮助内容
 void help_mode()
{
	printf("###################################################\n");
	printf("欢迎使用创新工场智能密码锁！\n");
	printf("注意:初次使用时进入管理模式，添加新用户\n");
	printf("1、本密码锁有两种工作模式，根据提示输入数\n");
	printf("字1、2即可选择不同工作模式。\n");
	printf("2、在用户模式下：可以根据提示输入用户名字和密码\n");
	printf("开锁，密码正确的情况下可以修改保存密码。\n");
	printf("3、在管理模式下：可以根据提示输入密码开锁，密码\n");
	printf("正确的情况下可以修改管理员密码、创建新用户。\n");
	printf("在各个模式下可以选择退出\n");
	printf("###################################################\n");
	
}
//###################################################################

void quit()
{   
    int a;
	printf("选择离开，请输入:离开（1），继续（2）\n");
	scanf("%d",&a);
	if(a==1)
		{   
             a=0;
			//goto next;
		}

}

//初始化
void init()
{
	work_mode=menu_show();
}
//###################################################

//读入用户信息
void user_mes()
{     
      printf("##################################################\n");
      printf("Please input user name:");
      scanf("%s",uname);
      sleep(1);
	  printf("##################################################\n");
      printf("Please input user password:");
      scanf("%s",pawd);
      path=uname;
      strcat(path,".txt");
      //printf("%s\n",path);
      //printf("%s\n",pawd);
}
//##############################################################

//主程序
void main()
{    
     int a;
     key_check();
     next:
     //key_check();
     init();
	 //#################################################
	 //用户模式
     if(work_mode==1)
		 
     {
         once:
		 user_mes();
		 user();
		 printf("##################################################\n");
		 printf("你要回主菜单吗？，是(1),否(2):\n");
	     scanf("%d",&a);
	     if(a==1)
		{   
              a=0;
		      goto next;
		}
         else
             goto once;
     }
	 //#########################
	 //管理模式
	 if(work_mode==2)
	 {   
             admin:
	         admin();
			 printf("##################################################\n");
             printf("你要回主菜单吗？，是(1),否(2):\n");
	         scanf("%d",&a);
	        if(a==1)
		      {   
                     a=0;
		             goto next;
		      }
            else
              {
                     goto admin; 
              }
                
		 //quit();
	 }
	 //#########################
	 //帮助？
	 if(work_mode==3)
	 {          
		 help_mode();
         next1:
		 printf("##################################################\n");
         printf("选择离开，请输入:离开（1）\n");
	     scanf("%d",&a);
	     if(a==1)
		{   
            a=0;
			goto next;
		}
         else
            goto next1;
	 }
	   
}
