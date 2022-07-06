/*
   #include <unistd.h>

   extern char **environ;

   int execl(const char *pathname, const char *arg, ...);
      参数：
         -path:需要指定的执行的文件的路径或名称
            a.out  或 /home/xxx/a.out(*推荐)
         -arg: 是可执行文件需要的参数列表
         
         注：第一个参数一般没有什么作用，为了方便，一般写的是程序的名称
            第二个参数开始往后，就是程序运行需要的参数列表，参数最后以哨兵（NULL）结尾
      返回值：
         只有当调用失败才会有返回值，调用失败，返回-1，并设置errno，可通过perror打印；调用成功，则不返回。
   

   l(list):参数地址列表，以空指针结尾
   v(vector):存有各参数地址的指针数组的地址
   p(path):按 PATH 环境变量指定的目录搜索可执行文件
   e(environment):存有环境变量字符串地址的指针数组的地址
*/
#include <unistd.h>
#include <stdio.h>
int main(){
   //创建一个子进程，在子进程中执行exec函数族中的函数
   pid_t pid = fork();

   if(pid > 0){
      //父进程
      printf("I am parent process, pid : %d\n", getpid());
   }else if(pid == 0){
      //子进程
      //execl("hello", "hello", NULL);
      execl("/usr/bin/ping","ping", "127.0.0.1", NULL);
      printf("I am child process, pid : %d\n", getpid());
   }
   
   for(int i = 0; i < 3; i++){
      printf("i = %d, pid = %d\n", i, getpid());
      sleep(1);
   }
}
