/*
   #include <sys/types.h>
   #include <unistd.h>

   pid_t fork(void);
      作用：创建一个子进程
      返回值：
         fork()的返回值会返回两次，一次在父进程中，另一次在子进程中。
         成功：父进程返回子进程pid，子进程返回0
         失败：父进程返回-1, 子进程未被创建，并且设置errno
            errno: 
               -EAGAIN: 系统进程数达到上限
               -ENOMEM: 系统内存不足
         如何区分父子进程：通过fork()的返回值。
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
   //创建子进程
   pid_t pid = fork();

   //判断是父进程还是子进程
   if(pid > 0){
      printf("%d\n", pid);
      //如果大于0，返回的是子进程的进程号,当前是父进程
      printf("I'm parent process, pid : %d, ppid : %d\n", getpid(), getppid());
   }else if(pid == 0){
      //当前是子进程
      printf("I'm child process, pid : %d, ppid : %d\n", getpid(), getppid());
   }
   
   //for循环输出一组数
   for(int i = 0; i < 5; i++){
      printf("i : %d\n", i);
      sleep(1);
   }

   return 0;
}