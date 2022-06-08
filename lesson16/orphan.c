#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
   int num = 10;
   //创建子进程
   pid_t pid = fork();

   //判断是父进程还是子进程
   if(pid > 0){
      printf("I'm parent process, pid : %d, ppid : %d\n", getpid(), getppid());
      
   }else if(pid == 0){
      //当前是子进程
      sleep(1);
      printf("I'm child process, pid : %d, ppid : %d\n", getpid(), getppid());
      
   }
   
   //for循环输出一组数
   for(int i = 0; i < 5; i++){
      printf("i : %d, pid : %d\n", i, getpid());
   }

   return 0;
}