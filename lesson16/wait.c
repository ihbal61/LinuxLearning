/*
   #include <sys/types.h>
   #include <sys/wait.h>

   pid_t wait(int *wstatus);
      功能：等待任意一个子进程结束，如果任意一个子进程结束，此函数就会回收子进程的资源
      参数：
         -int *wstatus：进程退出时的状态信息，传入的时一个int类型的地址，传出参数。
      返回值：
         -成功：返回结束的（被回收的）子进程的进程id
         -失败：返回-1(所有的子进程都已回收或调用函数失败)

   调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）
   如果没有子进程了，函数立刻返回-1；如果子进程都已经结束了，也会立即返回-1

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