/*
   #include <sys/types.h>
   #include <sys/wait.h>

   pid_t waitpid(pid_t pid, int *wstatus, int options);
      功能：回收指定进程号的子进程，可以设置是否阻塞（默认阻塞）。
      参数：
         -pid :
            pid > 0 : 某个子进程的pid
            pid = 0: 回收当前进程组的所有子进程
            pid = -1 : 回收所有的子进程, 相当于 wait()   (最常用)
            pid < -1 : 回收某个进程组的组id的绝对值，回收指定进程组中的子进程
         -*wstatus : 进程退出时的状态信息，传入的时一个int类型的地址，传出参数。
         -options : 设置阻塞或非阻塞
            0 ： 阻塞
            WNOHANG ： 非阻塞

         waitpid(-1, &wstatus, 0)  <=>  wait()

      返回值：
         > 0 : 返回子进程的id
         = 0 ： options=WNOHANG, 表示还有子进程
         = -1 ： 错误， 或者没有子进程了

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
         sleep(1);
         int st;
         //int ret = waitpid(-1, &st, 0);//阻塞
         int ret = waitpid(-1, &st, WNOHANG);//非阻塞
         if(ret == -1){
            break;
         }else if(ret == 0){
            //说明还有子进程存在
            continue;
         }else if(ret > 0){
            if(WIFEXITED(st)){
               //是否是正常退出
               printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }
            if(WIFSIGNALED(st)){
               //是否是异常终止
               printf("被 %d 号信号干掉了\n", WTERMSIG(st));
            }
            printf("child die, pid = %d\n", ret);
         }
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