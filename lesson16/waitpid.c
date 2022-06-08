/*
   #include <sys/types.h>
   #include <sys/wait.h>

   pid_t waitpid(pid_t pid, int *wstatus, int options);
      功能：
      参数：
      返回值：
         -成功：返回状态改变的子进程的进程id，如果制定了WNOHANG， 并且存在一个或多个由pid指定的子进程，但其状态尚未更改，返回0
         -失败：返回-1

*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
   // 有一个父进程，创建5个子进程
   pid_t pid;
   //创建5个子进程
   for(int i = 0; i < 2; i++){
      pid = fork();
      if(pid == 0){
         break;
      }
   }
   
   if(pid > 0){
      //父进程
      while(1){
         printf("I'm parent process, pid : %d\n", getpid());

         int ret = wait(NULL);
         if(ret == -1){
            break;
         }
         printf("child die, pid = %d\n", ret);

         sleep(1);
      }
   }else if(pid == 0){
      //子进程
      while(1){
         printf("I'm child process, pid : %d\n", getpid());
         sleep(1);
      }
   }

   return 0;
}