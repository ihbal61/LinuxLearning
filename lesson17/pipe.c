/*
   #include <unistd.h>

   int pipe(int pipefd[2]);
      功能：创建一个匿名管道，用来进程间通信
      参数：int pipefd[2] 数组是一个传出参数
         -pipefd[0] : 对应管道的读端
         -pipefd[1] ：对应管道的写端
      返回值：
         成功：返回0
         失败：返回-1，设置errno

   管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞

   注意：匿名管道只能用于父子进程或兄弟进程之间的通信
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
//子进程发送数据给父进程，父进程读取数据输出
int main(){

   //fork之前创建管道
   int pipefd[2];
   int ret = pipe(pipefd);

   if(ret == -1){
      perror("pipe");
      exit(0);
   }
   //创建子进程
   pid_t pid = fork();
   if(pid > 0){
      //父进程
      
      printf("I am parent process, pid : %d\n", getpid());

      //关闭写端
      close(pipefd[1]);

      char buf[1024] = {0};
      while(1){
         //从管道读取数据
         int len = read(pipefd[0], buf, sizeof(buf));
         printf("parent recv : %s, pid : %d\n", buf, getpid());

         //向管道写入数据
         // char* str = "hello, I am parent";
         // write(pipefd[1], str ,strlen(str));
         // sleep(1);
         // bzero(buf, 1024);
      }

   }else if(pid == 0){
      //子进程
      //往管道写入数据
      printf("I am child process, pid : %d\n", getpid());

      //关闭读端
      close(pipefd[0]);

      char buf[1024] = {0};
      while(1){
         //向管道写入数据
         char* str = "hello, I am child\n";
         write(pipefd[1], str ,strlen(str));
         //sleep(1);

         // 从管道读取数据
         // int len = read(pipefd[0], buf, sizeof(buf));
         // printf("child recv : %s, pid : %d\n", buf, getpid());
         // bzero(buf, 1024);
      }

   }

   return 0;
}