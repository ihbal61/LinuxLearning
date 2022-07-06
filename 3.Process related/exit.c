/*
   #include <unistd.h>

   void _exit(int status);
      参数：
         -status:进程退出时的一个状态信息，父进程回收子进程资源得到时候可以获取
      作用：退出进程
   #include <stdlib.h>

   void exit(int status);
      作用：退出进程，在退出之前调用退出处理函数，刷新I/O缓冲，关闭文件描述符
*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(){
   printf("hello\n");
   printf("world");

   _exit(0);
   //exit(0);
   
   //return 0;
}